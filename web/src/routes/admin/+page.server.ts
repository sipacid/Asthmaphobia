import { redirect } from '@sveltejs/kit';
import type { PageServerLoad } from './$types';
import { downloads, user } from '$lib/server/db/schema';
import { db } from '$lib/server/db';
import { count } from 'drizzle-orm';

export const load: PageServerLoad = async (event) => {
	if (!event.locals.user) {
		return redirect(302, '/auth/login');
	}
	if (event.locals.user.role !== 'administrator') {
		return redirect(302, '/dashboard');
	}

	const totalDownloads = (await db.select({ total: count() }).from(downloads))[0].total;
	const totalUsers = (await db.select({ total: count() }).from(user))[0].total;

	return {
		user: event.locals.user,
        totalDownloads,
        totalUsers
	};
};
