<script lang="ts">
	import { onMount } from 'svelte';
	import type { PageServerData } from './$types';
	import FaqItem from '$lib/components/FaqItem.svelte';

	let { data }: { data: PageServerData } = $props();
	const faqs = data.faqs;
	const updates = data.updates;

	const features = [
		{
			title: 'Visual Cheats',
			description: 'ESP for ghosts, evidence, players, fuseboxes and detailed ghost info window',
			icon: 'M9 12l2 2 4-4m5.618-4.016A11.955 11.955 0 0112 2.944a11.955 11.955 0 01-8.618 3.04A12.02 12.02 0 003 9c0 5.591 3.824 10.29 9 11.622 5.176-1.332 9-6.03 9-11.622 0-1.042-.133-2.052-.382-3.016z'
		},
		{
			title: 'Movement Hacks',
			description: 'NoClip through walls, Speed hacks, Teleport and Infinite Stamina',
			icon: 'M12 6.253v13m0-13C10.832 5.477 9.246 5 7.5 5S4.168 5.477 3 6.253v13C4.168 18.477 5.754 18 7.5 18s3.332.477 4.5 1.253m0-13C13.168 5.477 14.754 5 16.5 5c1.747 0 3.332.477 4.5 1.253v13C19.832 18.477 18.247 18 16.5 18c-1.746 0-3.332.477-4.5 1.253'
		},
		{
			title: 'Player & Ghost Mods',
			description: 'GodMode, Player Modifications, Ghost Control and Direct Ghost Interaction',
			icon: 'M9 5H7a2 2 0 00-2 2v12a2 2 0 002 2h10a2 2 0 002-2V7a2 2 0 00-2-2h-2M9 5a2 2 0 002 2h2a2 2 0 002-2M9 5a2 2 0 012-2h2a2 2 0 012 2m-3 7h3m-3 4h3m-6-4h.01M9 16h.01'
		},
		{
			title: 'Game Exploits',
			description: 'Anti-Kick, Custom Name, Door Control, and Reward Modifications',
			icon: 'M9 20l-5.447-2.724A1 1 0 013 16.382V5.618a1 1 0 011.447-.894L9 7m0 13l6-3m-6 3V7m6 10l4.553 2.276A1 1 0 0021 18.382V7.618a1 1 0 00-.553-.894L15 4m0 13V4m0 0L9 7'
		}
	];

	const testimonials = [
		{
			author: 'Sky3rr',
			content: 'A highly intelligent developer, created features no one else had thought of.',
			rating: 5
		}
	];

	const screenshots = [
		{
			src: '/images/img-1.webp',
			alt: 'Soon TM',
			caption: 'Soon TM'
		},
		{
			src: '/images/img-2.webp',
			alt: 'Soon TM',
			caption: 'Soon TM'
		},
		{
			src: '/images/img-3.webp',
			alt: 'Soon TM',
			caption: 'Soon TM'
		}
	];

	// Animation for the hero section
	let heroAnimated = $state(false);

	onMount(() => {
		setTimeout(() => {
			heroAnimated = true;
		}, 300);
	});
</script>

<svelte:head>
	<title>Asthmaphobia - Advanced Phasmophobia Cheat</title>
	<meta
		name="description"
		content="The ultimate cheat tool for Phasmophobia with ESP, NoClip and more"
	/>
</svelte:head>

<div class="min-h-screen bg-black">
	<div class="relative">
		<div
			class="absolute inset-0 bg-gradient-to-b from-purple-900/20 via-transparent to-transparent opacity-60"
		></div>
		<div class="relative z-10 container mx-auto max-w-6xl px-4 py-8">
			<!-- Hero Section -->
			<section class="pt-16 pb-20">
				<div
					class="relative overflow-hidden rounded-3xl border border-zinc-800/40 bg-zinc-900/70 p-8 shadow-xl backdrop-blur-md md:p-12"
				>
					<div
						class="absolute inset-0 bg-gradient-to-r from-purple-900/20 to-blue-900/20 opacity-30"
					></div>
					<div class="absolute -inset-[500px] -z-10">
						<div
							class="absolute top-1/2 left-1/2 h-[800px] w-[800px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-purple-500/20 blur-[100px]"
						></div>
						<div
							class="absolute top-1/3 right-1/3 h-[600px] w-[600px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-blue-500/10 blur-[120px]"
						></div>
					</div>

					<div class="relative z-10">
						<div class="flex flex-col items-center text-center">
							<div
								class="mb-4 inline-block rounded-full bg-gradient-to-r from-purple-500/20 to-purple-700/20 px-4 py-1.5 backdrop-blur-sm"
							>
								<span class="text-sm font-medium text-purple-300">v2.4.0 — Latest Release</span>
							</div>

							<h1
								class="mb-4 text-5xl font-bold text-white transition-all duration-700 md:text-6xl"
								class:scale-105={heroAnimated}
							>
								<span
									class="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent"
									>Asthmaphobia</span
								>
							</h1>

							<p
								class="mb-8 max-w-xl text-lg text-zinc-300 transition-all delay-200 duration-700"
								class:opacity-100={heroAnimated}
								class:translate-y-0={heroAnimated}
								class:opacity-0={!heroAnimated}
								class:translate-y-4={!heroAnimated}
							>
								The most advanced and undetected cheat for Phasmophobia. Dominate the paranormal
								realm with powerful ESP, movement hacks, and ghost control.
							</p>

							<div
								class="mb-8 grid w-full max-w-3xl gap-6 transition-all delay-300 duration-700 md:grid-cols-3"
								class:opacity-100={heroAnimated}
								class:translate-y-0={heroAnimated}
								class:opacity-0={!heroAnimated}
								class:translate-y-4={!heroAnimated}
							>
								<div
									class="flex flex-col items-center rounded-xl border border-zinc-800/50 bg-black/30 p-4 backdrop-blur-md"
								>
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="mb-2 h-7 w-7 text-purple-500"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M9 12l2 2 4-4m5.618-4.016A11.955 11.955 0 0112 2.944a11.955 11.955 0 01-8.618 3.04A12.02 12.02 0 003 9c0 5.591 3.824 10.29 9 11.622 5.176-1.332 9-6.03 9-11.622 0-1.042-.133-2.052-.382-3.016z"
										/>
									</svg>
									<h3 class="mb-1 font-semibold text-white">Undetected</h3>
									<p class="text-center text-sm text-zinc-400">
										Advanced stealth technology stays hidden from anti-cheat
									</p>
								</div>

								<div
									class="flex flex-col items-center rounded-xl border border-zinc-800/50 bg-black/30 p-4 backdrop-blur-md"
								>
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="mb-2 h-7 w-7 text-purple-500"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M12 6V4m0 2a2 2 0 100 4m0-4a2 2 0 110 4m-6 8a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4m6 6v10m6-2a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4"
										/>
									</svg>
									<h3 class="mb-1 font-semibold text-white">Feature-Rich</h3>
									<p class="text-center text-sm text-zinc-400">
										Over 30+ powerful features to enhance your gameplay
									</p>
								</div>

								<div
									class="flex flex-col items-center rounded-xl border border-zinc-800/50 bg-black/30 p-4 backdrop-blur-md"
								>
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="mb-2 h-7 w-7 text-purple-500"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M4 4v5h.582m15.356 2A8.001 8.001 0 004.582 9m0 0H9m11 11v-5h-.581m0 0a8.003 8.003 0 01-15.357-2m15.357 2H15"
										/>
									</svg>
									<h3 class="mb-1 font-semibold text-white">Constant Updates</h3>
									<p class="text-center text-sm text-zinc-400">
										Regular updates to match game patches and add new features
									</p>
								</div>
							</div>

							<div
								class="mt-2 flex flex-col justify-center gap-4 transition-all delay-400 duration-700 sm:flex-row"
								class:opacity-100={heroAnimated}
								class:translate-y-0={heroAnimated}
								class:opacity-0={!heroAnimated}
								class:translate-y-4={!heroAnimated}
							>
								<a
									href="/dashboard"
									class="group relative overflow-hidden rounded-xl bg-gradient-to-r from-purple-600 to-indigo-600 px-8 py-3.5 text-center font-medium text-white shadow-lg transition-all hover:from-purple-500 hover:to-indigo-500 focus:ring-2 focus:ring-purple-500 focus:ring-offset-2 focus:ring-offset-black focus:outline-none"
								>
									<div class="relative z-10 flex items-center justify-center">
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
												d="M4 16v1a3 3 0 003 3h10a3 3 0 003-3v-1m-4-4l-4 4m0 0l-4-4m4 4V4"
											/>
										</svg>
										Download Latest Version
									</div>
									<div
										class="absolute inset-0 -translate-y-full bg-gradient-to-r from-purple-600/30 to-indigo-600/30 transition-transform duration-300 ease-out group-hover:translate-y-0"
									></div>
								</a>
								<a
									href="/features"
									class="rounded-xl border border-purple-700/50 bg-purple-900/10 px-8 py-3.5 text-center font-medium text-purple-300 backdrop-blur-sm transition-all hover:bg-purple-900/30 hover:text-purple-200 focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black focus:outline-none"
								>
									View All Features
								</a>
							</div>
						</div>
					</div>
				</div>
			</section>

			<!-- Screenshots Showcase -->
			<section class="mb-16">
				<h2 class="mb-8 flex items-center text-2xl font-bold text-white">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-2 h-6 w-6 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M4 16l4.586-4.586a2 2 0 012.828 0L16 16m-2-2l1.586-1.586a2 2 0 012.828 0L20 14m-6-6h.01M6 20h12a2 2 0 002-2V6a2 2 0 00-2-2H6a2 2 0 00-2 2v12a2 2 0 002 2z"
						/>
					</svg>
					See It In Action
				</h2>

				<div class="grid gap-6 md:grid-cols-3">
					{#each screenshots as screenshot (screenshot.src)}
						<div
							class="group relative overflow-hidden rounded-xl border border-zinc-800/50 bg-zinc-900/50 shadow-lg transition-all hover:border-purple-600/30"
						>
							<div
								class="absolute inset-0 z-10 bg-gradient-to-t from-black to-transparent opacity-0 transition-opacity group-hover:opacity-60"
							></div>
							<img
								src={screenshot.src}
								alt={screenshot.alt}
								class="h-60 w-full object-cover transition-transform duration-500 group-hover:scale-105"
							/>
							<div
								class="absolute right-0 bottom-0 left-0 z-20 translate-y-full transform p-3 text-white transition-transform group-hover:translate-y-0"
							>
								<p class="text-sm font-medium">{screenshot.caption}</p>
							</div>
						</div>
					{/each}
				</div>
			</section>

			<!-- Features Section -->
			<section class="mb-16">
				<h2 class="mb-8 flex items-center text-2xl font-bold text-white">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-2 h-6 w-6 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M11 4a2 2 0 114 0v1a1 1 0 001 1h3a1 1 0 011 1v3a1 1 0 01-1 1h-1a2 2 0 100 4h1a1 1 0 011 1v3a1 1 0 01-1 1h-3a1 1 0 01-1-1v-1a2 2 0 10-4 0v1a1 1 0 01-1 1H7a1 1 0 01-1-1v-3a1 1 0 00-1-1H4a2 2 0 110-4h1a1 1 0 001-1V7a1 1 0 011-1h3a1 1 0 001-1V4z"
						/>
					</svg>
					Key Features
				</h2>

				<div class="grid gap-6 sm:grid-cols-2 lg:grid-cols-4">
					{#each features as feature (feature.title)}
						<div
							class="group rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 backdrop-blur-sm transition-all duration-300 hover:scale-[1.02] hover:border-purple-600/30 hover:bg-zinc-900/70"
						>
							<div
								class="mb-4 flex h-12 w-12 items-center justify-center rounded-lg bg-gradient-to-br from-purple-900/40 to-indigo-900/40 transition-colors duration-300 group-hover:from-purple-700/40 group-hover:to-indigo-600/40"
							>
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="h-6 w-6 text-purple-400 transition-colors duration-300 group-hover:text-purple-300"
									fill="none"
									viewBox="0 0 24 24"
									stroke="currentColor"
								>
									<path
										stroke-linecap="round"
										stroke-linejoin="round"
										stroke-width="2"
										d={feature.icon}
									></path>
								</svg>
							</div>
							<h3 class="mb-2 text-lg font-medium text-white">{feature.title}</h3>
							<p
								class="text-sm text-zinc-400 transition-colors duration-300 group-hover:text-zinc-300"
							>
								{feature.description}
							</p>
						</div>
					{/each}
				</div>
			</section>

			<!-- Testimonials -->
			<section class="mb-16">
				<h2 class="mb-8 flex items-center text-2xl font-bold text-white">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-2 h-6 w-6 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M8 12h.01M12 12h.01M16 12h.01M21 12c0 4.418-4.03 8-9 8a9.863 9.863 0 01-4.255-.949L3 20l1.395-3.72C3.512 15.042 3 13.574 3 12c0-4.418 4.03-8 9-8s9 3.582 9 8z"
						/>
					</svg>
					What Users Say
				</h2>

				<div class="grid gap-6 md:grid-cols-3">
					{#each testimonials as testimonial (testimonial.author)}
						<div
							class="rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 backdrop-blur-sm transition-transform hover:scale-[1.02]"
						>
							<div class="mb-4 flex text-yellow-500">
								{#each Array.from({ length: testimonial.rating }, (_, i) => i) as i (testimonial.author + '-star-' + i)}
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="h-5 w-5"
										viewBox="0 0 20 20"
										fill="currentColor"
									>
										<path
											d="M9.049 2.927c.3-.921 1.603-.921 1.902 0l1.07 3.292a1 1 0 00.95.69h3.462c.969 0 1.371 1.24.588 1.81l-2.8 2.034a1 1 0 00-.364 1.118l1.07 3.292c.3.921-.755 1.688-1.54 1.118l-2.8-2.034a1 1 0 00-1.175 0l-2.8 2.034c-.784.57-1.838-.197-1.539-1.118l1.07-3.292a1 1 0 00-.364-1.118l-2.799-2.034c-.784-.57-.38-1.81.588-1.81h3.461a1 1 0 00.951-.69l1.07-3.292z"
										/>
									</svg>
								{/each}
							</div>
							<p class="mb-4 text-zinc-300 italic">"‎{testimonial.content}"</p>
							<p class="text-sm font-medium text-purple-400">— {testimonial.author}</p>
						</div>
					{/each}
				</div>
			</section>

			<!-- Updates Section -->
			<section class="mb-16">
				<h2 class="mb-8 flex items-center text-2xl font-bold text-white">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-2 h-6 w-6 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M13 10V3L4 14h7v7l9-11h-7z"
						/>
					</svg>
					Latest Updates
				</h2>

				<div class="space-y-4">
					{#each updates as update (update.createdAt)}
						<div
							class="rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 backdrop-blur-sm transition-all hover:border-purple-600/30"
						>
							<div class="mb-2 flex flex-wrap items-center justify-between gap-4">
								<h3 class="text-lg font-medium text-white">{update.title}</h3>
								<span class="text-sm text-zinc-500"
									>{new Date(update.createdAt!).toLocaleDateString()}</span
								>
							</div>
							<p class="text-zinc-400">{update.content}</p>
						</div>
					{/each}
				</div>
			</section>

			<!-- FAQ Section -->
			<section class="mb-16">
				<h2 class="mb-8 flex items-center text-2xl font-bold text-white">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-2 h-6 w-6 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M8.228 9c.549-1.165 2.03-2 3.772-2 2.21 0 4 1.343 4 3 0 1.4-1.278 2.575-3.006 2.907-.542.104-.994.54-.994 1.093m0 3h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
						/>
					</svg>
					Frequently Asked Questions
				</h2>

				<div class="space-y-4">
					{#each faqs as faq (faq.question)}
						<FaqItem question={faq.question} answer={faq.answer} />
					{/each}
				</div>
			</section>

			<!-- CTA Section -->
			<section class="mb-4">
				<div class="relative overflow-hidden rounded-3xl border border-zinc-800/40">
					<div
						class="absolute inset-0 bg-gradient-to-r from-purple-900/20 to-blue-900/20 opacity-30"
					></div>
					<div class="absolute -inset-[500px] -z-10">
						<div
							class="absolute top-1/3 left-1/3 h-[600px] w-[600px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-purple-500/20 blur-[100px]"
						></div>
					</div>

					<div class="relative z-10 p-10 text-center md:p-16">
						<h2 class="mb-6 text-3xl font-bold text-white md:text-4xl">
							Ready to Dominate Phasmophobia?
						</h2>
						<p class="mx-auto mb-8 max-w-2xl text-lg text-zinc-300">
							Join ghost hunters using Asthmaphobia to enhance their gameplay experience. Get
							instant access to all premium features.
						</p>

						<div class="flex flex-col items-center justify-center gap-4 sm:flex-row">
							<a
								href="/dashboard"
								class="group relative overflow-hidden rounded-xl bg-gradient-to-r from-purple-600 to-indigo-600 px-8 py-4 text-center font-medium text-white shadow-lg transition-all hover:from-purple-500 hover:to-indigo-500 focus:ring-2 focus:ring-purple-500 focus:ring-offset-2 focus:ring-offset-black focus:outline-none"
							>
								<div class="relative z-10 flex items-center justify-center">Get Started Now</div>
								<div
									class="absolute inset-0 -translate-y-full bg-gradient-to-r from-purple-600/30 to-indigo-600/30 transition-transform duration-300 ease-out group-hover:translate-y-0"
								></div>
							</a>
							<a
								href="/support"
								class="rounded-xl border border-purple-700/50 bg-purple-900/10 px-8 py-4 text-center font-medium text-purple-300 backdrop-blur-sm transition-all hover:bg-purple-900/30 hover:text-purple-200 focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black focus:outline-none"
							>
								Get Support
							</a>
						</div>
					</div>
				</div>
			</section>
		</div>
	</div>
</div>
