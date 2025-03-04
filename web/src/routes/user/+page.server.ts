import * as auth from '$lib/server/auth';
import { fail, redirect } from '@sveltejs/kit';
import type { Actions, PageServerLoad } from './$types';
import { UserError, userService } from '$lib/server/services/user';

export const load: PageServerLoad = async ({ locals }) => {
	if (!locals.user) {
		return redirect(302, '/auth/login');
	}

	return { user: locals.user };
};

export const actions: Actions = {
	logout: async (event) => {
		if (!event.locals.session) {
			return fail(401);
		}
		await auth.invalidateSession(event.locals.session.id);
		auth.deleteSessionTokenCookie(event);

		return redirect(302, '/auth/login');
	},
	update: async (event) => {
		if (!event.locals.user) {
			return fail(401, { message: 'You must be logged in to update your profile' });
		}

		const formData = await event.request.formData();
		const userId = formData.get('user-id')?.toString();
		const email = formData.get('email')?.toString();
		const username = formData.get('username')?.toString();
		const currentPassword = formData.get('current-password')?.toString();
		const newPassword = formData.get('password')?.toString();
		const confirmPassword = formData.get('confirm-password')?.toString();

		if (userId !== event.locals.user.id) {
			return fail(403, { message: 'You can only update your own profile' });
		}

		try {
			if (email || username) {
				await userService.updateUser({
					id: userId,
					email,
					username
				});
			}

			if (newPassword) {
				if (!currentPassword) {
					return fail(400, { message: 'Current password is required to change your password' });
				}

				if (newPassword !== confirmPassword) {
					return fail(400, { message: 'New passwords do not match' });
				}

				await userService.changePassword(userId, currentPassword, newPassword);
			}
		} catch (error) {
			if (error instanceof UserError) {
				return fail(400, { message: error.message });
			}

			console.error('Error updating user:', error);
			return fail(500, { message: 'An error occurred while updating your profile' });
		}

		return { success: true };
	}
};
