<script lang="ts">
	/**
	 * SEO Component for Asthmaphobia
	 * Makes it easy to add consistent SEO metadata to any page
	 */
	export let title = 'Asthmaphobia - Advanced Phasmophobia Cheat';
	export let description =
		'The ultimate cheat tool for Phasmophobia with ESP, NoClip and more. Dominate with advanced features and regular updates.';
	export let keywords =
		'phasmophobia cheat, phasmophobia hack, asthmaphobia, game cheats, esp hack, noclip, ghost control';
	export let ogImage = '/images/og-image.jpg';
	export let canonical = ''; // Will use current URL if empty
	export let type = 'website';

	import { page } from '$app/state';

	// Use provided canonical URL or fallback to current page URL
	const canonicalUrl = canonical || page.url.href;
</script>

<svelte:head>
	<!-- Primary Meta Tags -->
	<title>{title}</title>
	<meta name="title" content={title} />
	<meta name="description" content={description} />
	<meta name="keywords" content={keywords} />

	<!-- Canonical URL -->
	<link rel="canonical" href={canonicalUrl} />

	<!-- Open Graph / Facebook -->
	<meta property="og:type" content={type} />
	<meta property="og:url" content={canonicalUrl} />
	<meta property="og:title" content={title} />
	<meta property="og:description" content={description} />
	<meta property="og:image" content={ogImage} />

	<!-- Twitter -->
	<meta property="twitter:card" content="summary_large_image" />
	<meta property="twitter:url" content={canonicalUrl} />
	<meta property="twitter:title" content={title} />
	<meta property="twitter:description" content={description} />
	<meta property="twitter:image" content={ogImage} />
</svelte:head>
