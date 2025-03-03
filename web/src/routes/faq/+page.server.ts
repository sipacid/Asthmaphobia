import type { PageServerLoad } from './$types';
import { db } from '$lib/server/db';
import { faq } from '$lib/server/db/schema';
import { asc } from 'drizzle-orm';

export const load: PageServerLoad = async () => {
	const faqs = await db
		.select({
			question: faq.question,
			answer: faq.answer,
			ranking: faq.ranking
		})
		.from(faq)
		.orderBy(asc(faq.ranking));

	return {
		faqs
	};
};
