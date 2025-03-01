<script lang="ts">
	import Footer from '$lib/components/footer.svelte';
	import Header from '$lib/components/header.svelte';
	import '../app.css';

	let { children } = $props();
</script>

<Header />
<div class="pt-14"> 
  {@render children()}
</div>
<Footer />
