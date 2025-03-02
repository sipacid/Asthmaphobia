import { fail, redirect } from '@sveltejs/kit';
import * as auth from '$lib/server/auth';
import { userService, UserError } from '$lib/server/services/user';
import type { Actions, PageServerLoad } from './$types';
import { verifyRecaptchaToken } from '$lib/server/recaptcha';

export const load: PageServerLoad = async (event) => {
	if (event.locals.user) {
		return redirect(302, '/dashboard');
	}

	return {};
};

export const actions: Actions = {
	register: async (event) => {
		const formData = await event.request.formData();
		const email = formData.get('email')?.toString();
		const username = formData.get('username')?.toString();
		const password = formData.get('password')?.toString();
		const recaptchaToken = formData.get('recaptcha_token')?.toString() || '';

		if (!email || !username || !password) {
			return fail(400, { message: 'Missing required fields' });
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

		try {
			const id = await userService.createUser({
				email,
				username,
				password
			});

			const sessionToken = auth.generateSessionToken();
			const session = await auth.createSession(sessionToken, id);
			auth.setSessionTokenCookie(event, sessionToken, session.expiresAt);
		} catch (error) {
			if (error instanceof UserError) {
				return fail(400, { message: error.message });
			}

			console.error('Registration error:', error);
			return fail(500, { message: 'An error has occurred' });
		}

		return redirect(302, '/dashboard');
	}
};
