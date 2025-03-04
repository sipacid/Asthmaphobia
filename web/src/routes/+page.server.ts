import { db } from '$lib/server/db';
import { faq, posts } from '$lib/server/db/schema';
import { eq, gt, desc, asc } from 'drizzle-orm';
import type { PageServerLoad } from './$types';

export const load: PageServerLoad = async () => {
	const faqs = await db
		.select({
			question: faq.question,
			answer: faq.answer
		})
		.from(faq)
		.where(gt(faq.ranking, 0))
		.orderBy(asc(faq.ranking))
		.limit(4);

	console.log('faqs', faqs);

	const updates = await db
		.select({
			title: posts.title,
			content: posts.content,
			createdAt: posts.createdAt
		})
		.from(posts)
		.where(eq(posts.type, 'release'))
		.orderBy(desc(posts.createdAt))
		.limit(3);

	return {
		faqs,
		updates
	};
};
