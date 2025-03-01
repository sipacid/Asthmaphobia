import { fail, redirect } from '@sveltejs/kit';
import { userService, UserError } from '$lib/server/services/user';
import type { PageServerLoad, Actions } from './$types';

export const load: PageServerLoad = async (event) => {
	if (!event.locals.user) {
		throw redirect(302, '/auth/login');
	}
	if (event.locals.user.role !== 'administrator') {
		throw redirect(302, '/dashboard');
	}

	const users = await userService.getUsers();

	const url = new URL(event.request.url);
	const editId = url.searchParams.get('edit');
	let editUser = null;

	if (editId) {
		try {
			editUser = await userService.getUserByID(editId);
		} catch (error) {
			if (!(error instanceof UserError && error.code === 'NOT_FOUND')) {
				console.error('Error fetching user:', error);
			}
		}
	}

	return {
		users,
		editUser,
		currentUser: {
			id: event.locals.user.id
		}
	};
};

export const actions: Actions = {
	edit: async (event) => {
		if (!event.locals.user || event.locals.user.role !== 'administrator') {
			return fail(401, {
				success: false,
				message: 'Unauthorized'
			});
		}

		const formData = await event.request.formData();
		const id = formData.get('id')?.toString();
		const username = formData.get('username')?.toString();
		const email = formData.get('email')?.toString();
		const role = formData.get('role')?.toString() === 'administrator' ? 'administrator' : 'user';

		if (!id || !username || !email) {
			return fail(400, {
				success: false,
				message: 'Required fields are missing'
			});
		}

		try {
			await userService.updateUser({
				id,
				username,
				email,
				role
			});

			return { success: true };
		} catch (error) {
			if (error instanceof UserError) {
				return fail(error.code === 'NOT_FOUND' ? 404 : 400, {
					success: false,
					message: error.message
				});
			}

			console.error('Error updating user:', error);
			return fail(500, {
				success: false,
				message: 'Failed to update user'
			});
		}
	},
	delete: async (event) => {
		if (!event.locals.user || event.locals.user.role !== 'administrator') {
			return fail(401, {
				success: false,
				message: 'Unauthorized'
			});
		}

		const formData = await event.request.formData();
		const id = formData.get('id')?.toString();

		if (!id) {
			return fail(400, {
				success: false,
				message: 'User ID is required'
			});
		}

		if (id === event.locals.user?.id) {
			return fail(400, {
				success: false,
				message: 'You cannot delete your own account'
			});
		}

		try {
			await userService.deleteUser(id);
		} catch (error) {
			if (error instanceof UserError) {
				return fail(error.code === 'NOT_FOUND' ? 404 : 400, {
					success: false,
					message: error.message
				});
			}

			console.error('Error deleting user:', error);
			return fail(500, {
				success: false,
				message: 'Failed to delete user'
			});
		}

		return { success: true };
	}
};
