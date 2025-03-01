<script lang="ts">
	let { children } = $props();
</script>

<main class="min-h-[calc(100vh-3.5rem)] bg-black pt-6 text-white">
	{@render children()}
</main>
