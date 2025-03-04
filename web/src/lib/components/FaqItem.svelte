<script lang="ts">
	let { question, answer } = $props();
	let isOpen = $state(false);

	function toggle() {
		isOpen = !isOpen;
	}
</script>

<div
	class="overflow-hidden rounded-xl border border-zinc-800/50 bg-zinc-900/50 backdrop-blur-sm"
	itemscope
	itemprop="mainEntity"
	itemtype="https://schema.org/Question"
>
	<button
		class="flex w-full items-center justify-between px-6 py-4 text-left text-white focus:ring-2 focus:ring-purple-500 focus:outline-none focus:ring-inset"
		onclick={toggle}
		aria-expanded={isOpen}
		aria-controls="faq-answer-{question.replace(/\s+/g, '-').toLowerCase()}"
	>
		<h3 class="text-lg font-medium" itemprop="name">{question}</h3>
		<svg
			xmlns="http://www.w3.org/2000/svg"
			class="h-6 w-6 text-purple-400 transition-transform duration-200 {isOpen ? 'rotate-180' : ''}"
			fill="none"
			viewBox="0 0 24 24"
			stroke="currentColor"
		>
			<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 9l-7 7-7-7" />
		</svg>
	</button>

	{#if isOpen}
		<div
			class="px-6 pb-4 text-zinc-300"
			id="faq-answer-{question.replace(/\s+/g, '-').toLowerCase()}"
			itemscope
			itemprop="acceptedAnswer"
			itemtype="https://schema.org/Answer"
		>
			<div itemprop="text">
				{answer}
			</div>
		</div>
	{/if}
</div>
