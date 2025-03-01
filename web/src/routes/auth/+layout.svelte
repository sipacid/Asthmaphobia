<script lang="ts">
	import '../../app.css';
	
	let { children } = $props();
</script>

<main class="h-svh bg-black text-white">
	<div class="absolute top-4 left-4 z-10">
		<a href="/" class="flex items-center text-lg font-bold">
			<span class="text-purple-500">Asthma</span><span class="text-white">phobia</span>
		</a>
	</div>
	
	{@render children()}
</main>
