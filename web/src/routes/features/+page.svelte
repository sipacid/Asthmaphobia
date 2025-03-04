<script lang="ts">
	import Seo from '$lib/components/Seo.svelte';

	const features = [
		{
			id: 'visual-cheats',
			title: 'Visual Cheats',
			description: 'See ghosts, evidence, and players through walls with our advanced ESP features',
			details: [
				'Ghost ESP - See ghost positions through walls with customizable colors',
				'Player ESP - Track your teammates across the map',
				'Item ESP - Locate crucial evidence and items easily',
				'Ghost Info - View detailed ghost information and behavior stats',
				'Evidence Tracker - Automatically track discovered evidence'
			],
			icon: 'M15 12a3 3 0 11-6 0 3 3 0 016 0z M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z'
		},
		{
			id: 'movement-hacks',
			title: 'Movement Hacks',
			description:
				'Move freely through the game environment with our powerful movement modifications',
			details: [
				'NoClip - Pass through walls, doors, and other obstacles',
				'Speed Hack - Move at customizable speeds',
				'Infinite Stamina - Run without getting tired',
				'Teleportation - Instantly teleport to selected locations',
				'Anti-Fall Damage - Prevent falling damage'
			],
			icon: 'M12 6.253v13m0-13C10.832 5.477 9.246 5 7.5 5S4.168 5.477 3 6.253v13C4.168 18.477 5.754 18 7.5 18s3.332.477 4.5 1.253m0-13C13.168 5.477 14.754 5 16.5 5c1.747 0 3.332.477 4.5 1.253v13C19.832 18.477 18.247 18 16.5 18c-1.746 0-3.332.477-4.5 1.253'
		},
		{
			id: 'ghost-control',
			title: 'Ghost Control',
			description: 'Take command of the supernatural with our ghost manipulation features',
			details: [
				'Ghost Manipulation - Control ghost behavior and actions',
				'Force Interactions - Make ghosts interact with the environment',
				'Ghost Teleport - Move ghosts to specific locations',
				'Hunt Control - Start and stop ghost hunts at will',
				'Ghost Type Changing - Change the type of ghost during a mission'
			],
			icon: 'M9 5H7a2 2 0 00-2 2v12a2 2 0 002 2h10a2 2 0 002-2V7a2 2 0 00-2-2h-2M9 5a2 2 0 002 2h2a2 2 0 002-2M9 5a2 2 0 012-2h2a2 2 0 012 2m-3 7h3m-3 4h3m-6-4h.01M9 16h.01'
		},
		{
			id: 'game-exploits',
			title: 'Game Exploits',
			description: 'Enhance your gameplay with powerful game mechanics modifications',
			details: [
				'Anti-Kick Protection - Prevent being kicked from games',
				'Unlimited Money - Get unlimited funds for equipment',
				'Custom Player Name - Set any player name you want',
				'All Items Unlocked - Access all game items regardless of level',
				"Sanity Control - Manipulate your character's sanity levels"
			],
			icon: 'M9 20l-5.447-2.724A1 1 0 013 16.382V5.618a1 1 0 011.447-.894L9 7m0 13l6-3m-6 3V7m6 10l4.553 2.276A1 1 0 0021 18.382V7.618a1 1 0 00-.553-.894L15 4m0 13V4m0 0L9 7'
		}
	];
</script>

<Seo
	title="Asthmaphobia Features - Complete List of Phasmophobia Cheats and Hacks"
	description="Explore the full list of Asthmaphobia features including ESP, NoClip, Ghost Control, and more. Our cheat offers 30+ undetected features for Phasmophobia."
	keywords="phasmophobia features, asthmaphobia cheat features, phasmophobia esp, noclip, ghost control, game hacks"
	ogImage="/images/features-og.jpg"
/>

<div class="relative min-h-screen bg-black">
	<div
		class="absolute inset-0 bg-gradient-to-b from-purple-900/20 via-transparent to-transparent opacity-60"
	></div>

	<div class="relative z-10 container mx-auto max-w-6xl px-4 py-8">
		<!-- Header -->
		<header class="py-16 text-center">
			<h1 class="mb-4 text-4xl font-bold text-white md:text-5xl">
				<span class="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent">
					Asthmaphobia Features
				</span>
			</h1>
			<p class="mx-auto max-w-2xl text-xl text-zinc-300">
				Explore our comprehensive suite of features designed to enhance your Phasmophobia
				experience. Gain unprecedented control over the game with 30+ powerful tools.
			</p>
		</header>

		<!-- Feature Categories -->
		<section class="mb-20">
			<div class="grid gap-6 sm:grid-cols-2 lg:grid-cols-4">
				{#each features as feature (feature.id)}
					<a
						href="#{feature.id}"
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
						<h2 class="mb-2 text-lg font-medium text-white">{feature.title}</h2>
						<p
							class="text-sm text-zinc-400 transition-colors duration-300 group-hover:text-zinc-300"
						>
							{feature.description}
						</p>
					</a>
				{/each}
			</div>
		</section>

		<!-- Detailed Features -->
		{#each features as feature (feature.id)}
			<section id={feature.id} class="mb-16 scroll-mt-20">
				<div class="rounded-2xl border border-zinc-800/50 bg-zinc-900/20 p-8 backdrop-blur-sm">
					<div class="mb-6 flex items-center">
						<div
							class="mr-4 flex h-12 w-12 items-center justify-center rounded-lg bg-gradient-to-br from-purple-800/60 to-indigo-800/60"
						>
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="h-6 w-6 text-purple-300"
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
						<h2 class="text-2xl font-bold text-white">{feature.title}</h2>
					</div>

					<p class="mb-6 text-zinc-300">{feature.description}</p>

					<h3 class="mb-3 text-lg font-semibold text-white">Key Capabilities:</h3>
					<ul class="space-y-2">
						{#each feature.details as detail (detail)}
							<li class="flex items-start">
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="mt-0.5 mr-2 h-5 w-5 text-purple-500"
									fill="none"
									viewBox="0 0 24 24"
									stroke="currentColor"
								>
									<path
										stroke-linecap="round"
										stroke-linejoin="round"
										stroke-width="2"
										d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z"
									/>
								</svg>
								<span class="text-zinc-300">{detail}</span>
							</li>
						{/each}
					</ul>
				</div>
			</section>
		{/each}

		<!-- CTA -->
		<section class="mt-20 mb-10">
			<div class="overflow-hidden rounded-xl border border-purple-700/30">
				<div
					class="relative bg-gradient-to-r from-purple-900/50 to-indigo-900/50 px-8 py-12 text-center"
				>
					<div class="absolute -inset-[500px] -z-10">
						<div
							class="absolute top-1/2 left-1/2 h-[600px] w-[600px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-purple-500/10 blur-[100px]"
						></div>
					</div>

					<h2 class="mb-4 text-3xl font-bold text-white">Ready to Experience These Features?</h2>
					<p class="mx-auto mb-8 max-w-2xl text-zinc-300">
						Download Asthmaphobia now and gain access to all these powerful features. Stay ahead of
						other ghost hunters with our regularly updated cheat software.
					</p>

					<div class="flex flex-col justify-center gap-4 sm:flex-row">
						<a
							href="/dashboard"
							class="group relative overflow-hidden rounded-xl bg-gradient-to-r from-purple-600 to-indigo-600 px-8 py-3.5 text-center font-medium text-white shadow-lg transition-all hover:from-purple-500 hover:to-indigo-500"
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
								Download Now
							</div>
							<div
								class="absolute inset-0 -translate-y-full bg-gradient-to-r from-purple-600/30 to-indigo-600/30 transition-transform duration-300 ease-out group-hover:translate-y-0"
							></div>
						</a>

						<a
							href="/support"
							class="rounded-xl border border-purple-700/50 bg-purple-900/10 px-8 py-3.5 text-center font-medium text-purple-300 backdrop-blur-sm transition-all hover:bg-purple-900/30 hover:text-purple-200"
						>
							Get Support
						</a>
					</div>
				</div>
			</div>
		</section>
	</div>
</div>
