<script lang="ts">
	let { question, answer } = $props();
	let isOpen = $state(false);

	function toggle() {
		isOpen = !isOpen;
	}
</script>

<button
	class={`w-full cursor-pointer rounded-xl border text-left hover:bg-zinc-800/20 ${
		isOpen ? 'border-purple-600/30' : 'border-zinc-800/50'
	} overflow-hidden bg-zinc-900/50 backdrop-blur-sm transition-all duration-300`}
	onclick={toggle}
	aria-expanded={isOpen}
	aria-controls={`faq-answer-${question.replace(/\s+/g, '-').toLowerCase()}`}
>
	<div class="flex w-full items-center justify-between p-6">
		<span class="text-lg font-medium text-white">{question}</span>
		<svg
			xmlns="http://www.w3.org/2000/svg"
			class={`h-5 w-5 text-purple-400 transition-transform duration-300 ${isOpen ? 'rotate-180' : ''}`}
			fill="none"
			viewBox="0 0 24 24"
			stroke="currentColor"
			aria-hidden="true"
		>
			<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 9l-7 7-7-7" />
		</svg>
	</div>

	<div
		class={`overflow-hidden transition-all duration-300 ${isOpen ? 'max-h-96' : 'max-h-0'}`}
		id={`faq-answer-${question.replace(/\s+/g, '-').toLowerCase()}`}
	>
		<div class="p-6 pt-0 text-zinc-400">{answer}</div>
	</div>
</button>
