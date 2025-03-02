<script lang="ts">
	import Footer from '$lib/components/footer.svelte';
	import Header from '$lib/components/header.svelte';
	import '../app.css';

	let { data, children } = $props();
</script>

<svelte:head>
	<script
		src="https://www.google.com/recaptcha/enterprise.js?render=6Le3ueYqAAAAAEhccxYc6Af7bBQrQYwSD5W1LYFO"
	></script>
</svelte:head>

<Header user={data.user} />
<div class="pt-14">
	{@render children()}
</div>
<Footer />
