import { fail, redirect } from '@sveltejs/kit';
import * as auth from '$lib/server/auth';
import { userService, UserError } from '$lib/server/services/user';
import type { Actions, PageServerLoad } from './$types';

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

		if (!email || !username || !password) {
			return fail(400, { message: 'Missing required fields' });
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
