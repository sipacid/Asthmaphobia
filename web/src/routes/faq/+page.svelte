<script lang="ts">
	import FaqItem from '$lib/components/FaqItem.svelte';
	import type { PageData } from './$types';

	let { data } = $props<{ data: PageData }>();
	const faqs = data.faqs;
	let searchQuery = $state('');

	function getFilteredFaqs() {
		const query = searchQuery.toLowerCase();

		if (!query) return faqs;

		return faqs.filter(
			(faq: any) =>
				faq.question.toLowerCase().includes(query) || faq.answer.toLowerCase().includes(query)
		);
	}
</script>

<svelte:head>
	<title>FAQ - Asthmaphobia</title>
	<meta name="description" content="Frequently Asked Questions about Asthmaphobia cheat tool" />
</svelte:head>

<div class="min-h-screen bg-black">
	<div class="relative">
		<div
			class="absolute inset-0 bg-gradient-to-b from-purple-900/20 via-transparent to-transparent opacity-60"
		></div>
		<div class="relative z-10 container mx-auto max-w-6xl px-4 py-8">
			<!-- Header -->
			<section>
				<div class="mt-8 mb-12 text-center">
					<h1 class="mb-4 text-4xl font-bold text-white md:text-5xl">
						<span class="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent"
							>Frequently Asked Questions</span
						>
					</h1>
					<p class="mx-auto max-w-2xl text-zinc-300">
						Get answers to the most common questions about Asthmaphobia. Can't find what you're
						looking for? Visit our <a href="/support" class="text-purple-400 hover:underline"
							>support page</a
						>.
					</p>
				</div>
			</section>

			<!-- Search and Filter -->
			<section class="mb-8">
				<div class="mb-6 flex flex-col gap-4 md:flex-row">
					<div class="flex-1">
						<div class="relative">
							<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="h-5 w-5 text-zinc-500"
									fill="none"
									viewBox="0 0 24 24"
									stroke="currentColor"
								>
									<path
										stroke-linecap="round"
										stroke-linejoin="round"
										stroke-width="2"
										d="M21 21l-6-6m2-5a7 7 0 11-14 0 7 7 0 0114 0z"
									/>
								</svg>
							</div>
							<input
								type="text"
								bind:value={searchQuery}
								placeholder="Search FAQs..."
								class="w-full rounded-lg border border-zinc-700 bg-zinc-800/50 p-2.5 pl-10 text-white placeholder-zinc-400 focus:border-purple-500 focus:ring-purple-500"
							/>
						</div>
					</div>
				</div>
			</section>

			<!-- FAQ Categories -->
			<section>
				{#if getFilteredFaqs().length > 0}
					<div class="space-y-4">
						{#each getFilteredFaqs() as faq}
							<FaqItem question={faq.question} answer={faq.answer} />
						{/each}
					</div>
				{:else}
					<div
						class="rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-8 text-center backdrop-blur-sm"
					>
						<svg
							xmlns="http://www.w3.org/2000/svg"
							class="mx-auto mb-4 h-12 w-12 text-zinc-500"
							fill="none"
							viewBox="0 0 24 24"
							stroke="currentColor"
						>
							<path
								stroke-linecap="round"
								stroke-linejoin="round"
								stroke-width="2"
								d="M9.172 16.172a4 4 0 015.656 0M9 10h.01M15 10h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
							/>
						</svg>
						<h3 class="mb-2 text-xl font-medium text-white">No results found</h3>
						<p class="text-zinc-400">
							No FAQs match your search criteria. Try adjusting your search filter.
						</p>
					</div>
				{/if}
			</section>

			<!-- Support CTA -->
			<section class="mt-16">
				<div
					class="rounded-3xl border border-zinc-800/40 bg-gradient-to-r from-purple-900/20 to-blue-900/20 p-8 text-center backdrop-blur-sm"
				>
					<h2 class="mb-4 text-2xl font-bold text-white">Still have questions?</h2>
					<p class="mb-6 text-zinc-300">
						If you couldn't find the answer you were looking for, our support team is ready to help.
					</p>
					<a
						href="/support"
						class="inline-flex items-center rounded-lg bg-gradient-to-r from-purple-600 to-indigo-600 px-5 py-2.5 text-center text-sm font-medium text-white hover:from-purple-500 hover:to-indigo-500 focus:ring-4 focus:ring-purple-900"
					>
						<svg
							xmlns="http://www.w3.org/2000/svg"
							class="mr-2 h-5 w-5"
							fill="none"
							viewBox="0 0 24 24"
							stroke="currentColor"
						>
							<path
								stroke-linecap="round"
								stroke-linejoin="round"
								stroke-width="2"
								d="M18.364 5.636l-3.536 3.536m0 5.656l3.536 3.536M9.172 9.172L5.636 5.636m3.536 9.192l-3.536 3.536M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
							/>
						</svg>
						Contact Support
					</a>
				</div>
			</section>
		</div>
	</div>
</div>
