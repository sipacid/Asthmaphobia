<script lang="ts">
	import { onNavigate } from '$app/navigation';
	import Footer from '$lib/components/Footer.svelte';
	import Header from '$lib/components/Header.svelte';
	import Seo from '$lib/components/Seo.svelte';
	import { type User } from '$lib/server/db/schema';
	import '../app.css';

	let { data, children } = $props();

	onNavigate((navigation) => {
		if (!document.startViewTransition) return;

		return new Promise((resolve) => {
			document.startViewTransition(async () => {
				resolve();
				await navigation.complete;
			});
		});
	});

	// Get default SEO config from layout data
	const defaultSeo = data.defaultSeo;
</script>

<Seo
	title={defaultSeo.title}
	description={defaultSeo.description}
	keywords={defaultSeo.keywords}
	ogImage={defaultSeo.ogImage}
/>

<svelte:head>
	<!-- Fallback Meta Tags (only used if page doesn't implement Seo component) -->
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<meta name="theme-color" content="#18181b" />

	<script
		src="https://www.google.com/recaptcha/enterprise.js?render=6Le3ueYqAAAAAEhccxYc6Af7bBQrQYwSD5W1LYFO"
	></script>
</svelte:head>

<Header user={data.user as User} />
<div class="pt-14">
	{@render children()}
</div>
<Footer />

<style>
	@keyframes fade-in {
		from {
			opacity: 0;
		}
	}

	@keyframes fade-out {
		to {
			opacity: 0;
		}
	}

	@keyframes slide-from-right {
		from {
			transform: translateX(30px);
		}
	}

	@keyframes slide-to-left {
		to {
			transform: translateX(-30px);
		}
	}

	:root::view-transition-old(root) {
		animation:
			90ms cubic-bezier(0.4, 0, 1, 1) both fade-out,
			300ms cubic-bezier(0.4, 0, 0.2, 1) both slide-to-left;
	}

	:root::view-transition-new(root) {
		animation:
			210ms cubic-bezier(0, 0, 0.2, 1) 90ms both fade-in,
			300ms cubic-bezier(0.4, 0, 0.2, 1) both slide-from-right;
	}
</style>
