import { fail, redirect } from '@sveltejs/kit';
import { userService, UserError } from '$lib/server/services/user';
import type { PageServerLoad, Actions } from './$types';
import { db } from '$lib/server/db';
import { userLogin } from '$lib/server/db/schema';
import { desc, eq } from 'drizzle-orm';

export const load: PageServerLoad = async (event) => {
	if (!event.locals.user) {
		throw redirect(302, '/auth/login');
	}
	if (event.locals.user.role !== 'administrator') {
		throw redirect(302, '/dashboard');
	}

	const users = await userService.getUsers();
	const editId = event.url.searchParams.get('edit');

	let editUser = null;
	if (editId) {
		editUser = await userService.getUserByID(editId);
	}

	return {
		user: event.locals.user,
		users,
		editUser
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
	},
	getUserDetails: async ({ request, locals }) => {
		if (!locals.user) {
			throw redirect(302, '/auth/login');
		}
		if (locals.user.role !== 'administrator') {
			throw redirect(302, '/dashboard');
		}

		const data = await request.formData();
		const userId = data.get('userId')?.toString();

		if (!userId) {
			return { success: false, error: 'User ID is required' };
		}

		try {
			const user = await userService.getUserByID(userId);

			if (!user) {
				return { success: false, error: 'User not found' };
			}

			const logins = await db
				.select({
					id: userLogin.id,
					userId: userLogin.userId,
					ipAddress: userLogin.ipAddress,
					userAgent: userLogin.userAgent,
					success: userLogin.success,
					createdAt: userLogin.createdAt
				})
				.from(userLogin)
				.where(eq(userLogin.userId, userId))
				.orderBy(desc(userLogin.createdAt))
				.limit(50);

			return {
				success: true,
				user: {
					id: user.id,
					username: user.username,
					email: user.email,
					role: user.role,
					createdAt: user.createdAt?.toISOString(),
					updatedAt: user.updatedAt?.toISOString()
				},
				userLogins: logins.map((login) => ({
					id: login.id,
					userId: login.userId,
					ipAddress: login.ipAddress,
					userAgent: login.userAgent,
					success: login.success,
					createdAt: login.createdAt?.toISOString()
				}))
			};
		} catch (error) {
			console.error('Error fetching user details:', error);
			return { success: false, error: 'Failed to fetch user details' };
		}
	}
};
