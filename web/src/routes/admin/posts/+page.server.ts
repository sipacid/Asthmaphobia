import { redirect } from '@sveltejs/kit';
import { db } from '$lib/server/db';
import { posts, user } from '$lib/server/db/schema';
import type { Actions, PageServerLoad } from './$types';
import { eq, desc } from 'drizzle-orm';
import { fail } from '@sveltejs/kit';

export const load: PageServerLoad = async (event) => {
	if (!event.locals.user) {
		throw redirect(302, '/auth/login');
	}
	if (event.locals.user.role !== 'administrator') {
		throw redirect(302, '/dashboard');
	}

	const editId = event.url.searchParams.get('edit');

	let editPost = null;
	if (editId) {
		const result = await db
			.select({
				id: posts.id,
				title: posts.title,
				content: posts.content,
				type: posts.type,
				published: posts.published
			})
			.from(posts)
			.where(eq(posts.id, editId))
			.limit(1);

		if (result.length > 0) {
			editPost = result[0];
		}
	}

	const allPosts = await db
		.select({
			id: posts.id,
			title: posts.title,
			type: posts.type,
			published: posts.published,
			created_at: posts.createdAt,
			updated_at: posts.updatedAt,
			author_id: posts.authorId,
			author_name: user.username
		})
		.from(posts)
		.innerJoin(user, eq(posts.authorId, user.id))
		.orderBy(desc(posts.createdAt));

	return {
		user: event.locals.user,
		posts: allPosts,
		editPost
	};
};

export const actions: Actions = {
	create: async (event) => {
		if (!event.locals.user || event.locals.user.role !== 'administrator') {
			return fail(401, {
				success: false,
				message: 'Unauthorized'
			});
		}

		const data = await event.request.formData();
		const title = data.get('title')?.toString();
		const content = data.get('content')?.toString();
		const type = data.get('type')?.toString();
		const published = data.get('published') === 'true';

		if (!title || !content || !type) {
			return fail(400, { success: false, error: 'Missing required fields' });
		}

		try {
			await db.insert(posts).values({
				title,
				content,
				type: type as 'news' | 'release',
				authorId: event.locals.user.id,
				published
			});
		} catch (error) {
			console.error('Error creating post:', error);
			return fail(500, { success: false, error: 'Failed to create post' });
		}

		return { success: true };
	},
	edit: async (event) => {
		if (!event.locals.user || event.locals.user.role !== 'administrator') {
			return fail(401, {
				success: false,
				message: 'Unauthorized'
			});
		}

		const data = await event.request.formData();
		const id = data.get('id')?.toString();
		const title = data.get('title')?.toString();
		const content = data.get('content')?.toString();
		const type = data.get('type')?.toString();
		const published = data.get('published') === 'true';

		if (!id || !title || !content || !type) {
			return fail(400, { success: false, error: 'Missing required fields' });
		}

		try {
			await db
				.update(posts)
				.set({
					title,
					content,
					type: type as 'news' | 'release',
					published,
					updatedAt: new Date()
				})
				.where(eq(posts.id, id));
		} catch (error) {
			if (error instanceof Response) throw error;

			console.error('Error updating post:', error);
			return fail(500, { success: false, error: 'Failed to update post' });
		}

		return { success: true };
	},
	delete: async (event) => {
		if (!event.locals.user || event.locals.user.role !== 'administrator') {
			return fail(401, {
				success: false,
				message: 'Unauthorized'
			});
		}

		const data = await event.request.formData();
		const id = data.get('id')?.toString();

		if (!id) {
			return fail(400, { success: false, error: 'Missing post ID' });
		}

		try {
			await db.delete(posts).where(eq(posts.id, id));
		} catch (error) {
			console.error('Error deleting post:', error);
			return fail(500, { success: false, error: 'Failed to delete post' });
		}

		return { success: true };
	}
};
