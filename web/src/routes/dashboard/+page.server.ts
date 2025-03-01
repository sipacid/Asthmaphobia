import { redirect } from '@sveltejs/kit';
import { db } from '$lib/server/db';
import { posts, user, downloads } from '$lib/server/db/schema';
import { eq, count, desc } from 'drizzle-orm';
import type { PageServerLoad } from './$types';

export const load: PageServerLoad = async (event) => {
	if (!event.locals.user) {
		return redirect(302, '/auth/login');
	}

	const allPosts = await db
		.select({
			id: posts.id,
			title: posts.title,
			content: posts.content,
			type: posts.type,
			author: {
				username: user.username
			},
			createdAt: posts.createdAt,
			updatedAt: posts.updatedAt
		})
		.from(posts)
		.where(eq(posts.published, true))
		.innerJoin(user, eq(posts.authorId, user.id))
		.orderBy(desc(posts.createdAt));
	const downloadCount = (await db.select({ total: count() }).from(downloads))[0].total;
	const latestRelease = allPosts.find((post) => post.type === 'release');
	const currentVersion = latestRelease?.version || '1.0.0';

	return {
		posts: allPosts,
		currentVersion,
		user: event.locals.user,
		supportedGameVersion: 'v7.0.0 - v7.1.2', // This could also come from a database table in the future
		releaseDate: latestRelease ? new Date(latestRelease.createdAt!).toDateString() : 'Unknown',
		downloadCount: downloadCount
	};
};
