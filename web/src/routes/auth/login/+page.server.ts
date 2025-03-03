import { fail, redirect } from '@sveltejs/kit';
import * as auth from '$lib/server/auth';
import { UserError, userService } from '$lib/server/services/user';
import { db } from '$lib/server/db';
import * as table from '$lib/server/db/schema';
import type { Actions, PageServerLoad } from './$types';
import { verifyRecaptchaToken } from '$lib/server/recaptcha';

export const load: PageServerLoad = async (event) => {
	if (event.locals.user) {
		return redirect(302, '/dashboard');
	}

	return {};
};

export const actions: Actions = {
	login: async (event) => {
		const formData = await event.request.formData();
		const email = formData.get('email')?.toString();
		const password = formData.get('password')?.toString();
		const recaptchaToken = formData.get('recaptcha_token')?.toString() || '';

		if (!email || !password) {
			return fail(400, { message: 'Email and password are required' });
		}

		const userAgent = event.request.headers.get('user-agent') || '';
		const forwarded = event.request.headers.get('x-forwarded-for');
		const ipAddress = forwarded ? forwarded.split(',')[0].trim() : event.getClientAddress();

		const recaptchaResult = await verifyRecaptchaToken(
			recaptchaToken,
			'login',
			userAgent,
			ipAddress
		);
		if (!recaptchaResult.success) {
			return fail(400, { message: recaptchaResult.message || 'reCAPTCHA verification failed' });
		}

		let existingUser = null;
		try {
			existingUser = await userService.getUserByEmail(email);
			if (!existingUser) {
				return fail(400, { message: 'Invalid email or password' });
			}

			if (!(await userService.isPasswordValid(password, existingUser.passwordHash))) {
				return fail(400, { message: 'Invalid email or password' });
			}

			const sessionToken = auth.generateSessionToken();
			const session = await auth.createSession(sessionToken, existingUser.id);
			auth.setSessionTokenCookie(event, sessionToken, session.expiresAt);

			await db.insert(table.userLogin).values({
				userId: existingUser.id,
				ipAddress: ipAddress,
				userAgent: event.request.headers.get('user-agent') || '',
				success: true
			});
		} catch (error) {
			if (existingUser)
				await db.insert(table.userLogin).values({
					userId: existingUser.id,
					ipAddress: ipAddress,
					userAgent: event.request.headers.get('user-agent') || '',
					success: true
				});

			if (error instanceof UserError) {
				return fail(400, { message: error.message });
			}

			console.error('Login error:', error);
			return fail(500, { message: 'Failed to authenticate' });
		}

		return redirect(302, '/dashboard');
	}
};
