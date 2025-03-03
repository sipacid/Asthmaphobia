import { redirect } from '@sveltejs/kit';
import { db } from '$lib/server/db';
import { faq } from '$lib/server/db/schema';
import type { Actions, PageServerLoad } from './$types';
import { eq, asc } from 'drizzle-orm';
import { fail } from '@sveltejs/kit';

export const load: PageServerLoad = async (event) => {
	if (!event.locals.user) {
		throw redirect(302, '/auth/login');
	}
	if (event.locals.user.role !== 'administrator') {
		throw redirect(302, '/dashboard');
	}

	const editId = event.url.searchParams.get('edit');

	let editFaq = null;
	if (editId) {
		const result = await db
			.select({
				id: faq.id,
				question: faq.question,
				answer: faq.answer,
				ranking: faq.ranking
			})
			.from(faq)
			.where(eq(faq.id, editId))
			.limit(1);

		if (result.length > 0) {
			editFaq = result[0];
		}
	}

	const faqs = await db
		.select({
			id: faq.id,
			question: faq.question,
			answer: faq.answer,
			ranking: faq.ranking,
			created_at: faq.createdAt,
			updated_at: faq.updatedAt
		})
		.from(faq)
		.orderBy(asc(faq.ranking));

	return {
		user: event.locals.user,
		faqs,
		editFaq: editFaq
	};
};

export const actions: Actions = {
	create: async (event) => {
		if (!event.locals.user || event.locals.user.role !== 'administrator') {
			return fail(401, { success: false, error: 'Unauthorized' });
		}

		const data = await event.request.formData();
		const question = data.get('question')?.toString();
		const answer = data.get('answer')?.toString();
		const ranking = data.get('ranking')?.toString() as unknown as number;

		// Validation
		if (!question || !answer || !ranking) {
			return fail(400, { success: false, error: 'Missing required fields' });
		}

		try {
			await db.insert(faq).values({
				question,
				answer,
				ranking
			});
		} catch (error) {
			console.error('Error creating FAQ:', error);
			return fail(500, { success: false, error: 'Failed to create FAQ' });
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
		const question = data.get('question')?.toString();
		const answer = data.get('answer')?.toString();
		const ranking = data.get('ranking')?.toString() as unknown as number;

		if (!id || !question || !answer || !ranking) {
			return fail(400, { success: false, error: 'Missing required fields' });
		}

		try {
			await db
				.update(faq)
				.set({
					question,
					answer,
					ranking,
					updatedAt: new Date()
				})
				.where(eq(faq.id, id));
		} catch (error) {
			if (error instanceof Response) throw error;

			console.error('Error updating FAQ:', error);
			return fail(500, { success: false, error: 'Failed to update FAQ' });
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
			return fail(400, { success: false, error: 'Missing FAQ ID' });
		}

		try {
			await db.delete(faq).where(eq(faq.id, id));
		} catch (error) {
			console.error('Error deleting FAQ:', error);
			return fail(500, { success: false, error: 'Failed to delete FAQ' });
		}

		return { success: true };
	}
};
