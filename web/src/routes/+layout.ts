export const load = async ({ data }) => {
	// Create default SEO config that can be extended by individual pages
	const defaultSeo = {
		title: 'Asthmaphobia - Advanced Phasmophobia Cheat',
		description:
			'The ultimate cheat tool for Phasmophobia with ESP, NoClip and more. Dominate with advanced features and regular updates.',
		keywords:
			'phasmophobia cheat, phasmophobia hack, asthmaphobia, game cheats, esp hack, noclip, ghost control',
		ogImage: '/images/og-image.jpg'
	};

	return {
		...data,
		defaultSeo
	};
};
