<script lang="ts">
	import type { PageServerData } from './$types';

	let { data }: { data: PageServerData } = $props();

	// Feature categories data
	const featureCategories = [
		{
			name: 'Ghost Hunting Tools',
			icon: `<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 12l2 2 4-4m5.618-4.016A11.955 11.955 0 0112 2.944a11.955 11.955 0 01-8.618 3.04A12.02 12.02 0 003 9c0 5.591 3.824 10.29 9 11.622 5.176-1.332 9-6.03 9-11.622 0-1.042-.133-2.052-.382-3.016z" />`,
			features: [
				{
					title: 'Evidence Tracking',
					description:
						'Track ghost evidence and automatically narrow down ghost types based on your findings'
				},
				{
					title: 'Ghost Type Database',
					description:
						'Comprehensive information about all ghost types, their evidence, strengths and weaknesses'
				},
				{
					title: 'EMF Level Visualization',
					description: 'Visual representation of EMF levels with history tracking'
				},
				{
					title: 'Spirit Box Recorder',
					description: 'Record and analyze Spirit Box responses for evidence collection'
				}
			]
		},
		{
			name: 'Mission Management',
			icon: `<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 5H7a2 2 0 00-2 2v12a2 2 0 002 2h10a2 2 0 002-2V7a2 2 0 00-2-2h-2M9 5a2 2 0 002 2h2a2 2 0 002-2M9 5a2 2 0 012-2h2a2 2 0 012 2m-3 7h3m-3 4h3m-6-4h.01M9 16h.01" />`,
			features: [
				{
					title: 'Objective Tracker',
					description: 'Track mission objectives and optional goals in real-time'
				},
				{
					title: 'Sanity Monitor',
					description:
						"Keep track of your team's sanity levels with alerts for dangerous thresholds"
				},
				{
					title: 'Activity Graph',
					description: 'Visualize ghost activity over time to predict hunting phases'
				},
				{
					title: 'Location Maps',
					description: 'Detailed maps of all game locations with key points of interest'
				}
			]
		},
		{
			name: 'Equipment Management',
			icon: `<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 6V4m0 2a2 2 0 100 4m0-4a2 2 0 110 4m-6 8a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4m6 6v10m6-2a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4" />`,
			features: [
				{
					title: 'Inventory Tracker',
					description: 'Keep track of all equipment carried by your team'
				},
				{
					title: 'Equipment Status',
					description: 'Monitor the status and battery levels of active equipment'
				},
				{
					title: 'Camera Feed Integration',
					description: 'View and manage video camera feeds directly in the overlay'
				},
				{
					title: 'Equipment Timer',
					description: 'Timer functions for smudge sticks, candles, and other timed equipment'
				}
			]
		},
		{
			name: 'Advanced Features',
			icon: `<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 10V3L4 14h7v7l9-11h-7z" />`,
			features: [
				{
					title: 'Voice Recognition',
					description: 'Use voice commands to control the overlay during gameplay'
				},
				{
					title: 'Custom Hotkeys',
					description: 'Configure custom hotkeys for quick actions without interrupting gameplay'
				},
				{
					title: 'Multi-Monitor Support',
					description: 'Position the overlay on any monitor in multi-monitor setups'
				},
				{
					title: 'Session Statistics',
					description: 'Track your ghost hunting performance across multiple games'
				}
			]
		},
		{
			name: 'Customization',
			icon: `<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M10.325 4.317c.426-1.756 2.924-1.756 3.35 0a1.724 1.724 0 002.573 1.066c1.543-.94 3.31.826 2.37 2.37a1.724 1.724 0 001.065 2.572c1.756.426 1.756 2.924 0 3.35a1.724 1.724 0 00-1.066 2.573c.94 1.543-.826 3.31-2.37 2.37a1.724 1.724 0 00-2.572 1.065c-.426 1.756-2.924 1.756-3.35 0a1.724 1.724 0 00-2.573-1.066c-1.543.94-3.31-.826-2.37-2.37a1.724 1.724 0 00-1.065-2.572c-1.756-.426-1.756-2.924 0-3.35a1.724 1.724 0 001.066-2.573c-.94-1.543.826-3.31 2.37-2.37.996.608 2.296.07 2.572-1.065z" />
			<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z" />`,
			features: [
				{
					title: 'UI Themes',
					description: 'Multiple UI themes including a specialized dark mode for night gameplay'
				},
				{
					title: 'Widget Layout',
					description: 'Customize the layout and visibility of individual overlay components'
				},
				{
					title: 'Transparency Control',
					description: 'Adjust the transparency of the overlay to match your preferences'
				},
				{
					title: 'Font Options',
					description: 'Change font size and style for better visibility during intense gameplay'
				}
			]
		}
	];

	// Track active category for mobile view
	let activeCategoryIndex = $state(0);

	// Parse content into bullet points for news items
	function parseContent(content: string): string[] {
		return content
			.split('\n')
			.filter((line) => line.trim().length > 0)
			.map((line) => (line.startsWith('- ') ? line.substring(2) : line));
	}

	// Track which news post is expanded
	let expandedPostId = $state(data.posts.length > 0 ? data.posts[0].id : '');

	// Toggle news post expansion
	const togglePost = (id: string) => {
		expandedPostId = expandedPostId === id ? '' : id;
	};
</script>

<div class="min-h-screen bg-black">
	<div class="container mx-auto max-w-6xl px-4 py-8">
		<!-- Hero Section -->
		<section class="mb-12">
			<div
				class="rounded-2xl border border-zinc-800 bg-zinc-900/70 p-6 text-center shadow-lg md:p-12"
			>
				<h1 class="mb-2 text-3xl font-bold text-white md:text-4xl">Asthmaphobia</h1>
				<p class="mb-6 text-lg text-zinc-400">
					The ultimate companion tool for Phasmophobia ghost hunters
				</p>

				<div
					class="mx-auto mb-8 flex max-w-sm flex-col items-center rounded-lg border border-zinc-800 bg-black/50 p-6 shadow-inner"
				>
					<div class="mb-4 flex items-baseline gap-2">
						<span class="text-2xl font-bold text-white">v{data.currentVersion}</span>
						<span class="rounded-full bg-purple-800/50 px-2 py-0.5 text-xs text-purple-300"
							>Latest</span
						>
					</div>

					<div class="mb-6 grid w-full grid-cols-2 gap-4 text-center">
						<div>
							<p class="text-xs text-zinc-500">Game Support</p>
							<p class="text-sm font-medium text-zinc-300">{data.supportedGameVersion}</p>
						</div>
						<div>
							<p class="text-xs text-zinc-500">Released</p>
							<p class="text-sm font-medium text-zinc-300">{data.releaseDate}</p>
						</div>
					</div>

					<a
						href="#download"
						class="group relative mb-4 w-full overflow-hidden rounded-lg bg-gradient-to-r from-purple-700 to-purple-600 px-8 py-3 text-center font-medium text-white shadow-lg transition-all hover:from-purple-600 hover:to-purple-500 focus:ring-2 focus:ring-purple-500 focus:ring-offset-2 focus:ring-offset-black focus:outline-none"
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
							class="absolute inset-0 -translate-y-full bg-gradient-to-r from-purple-600/30 to-purple-500/30 transition-transform duration-300 ease-out group-hover:translate-y-0"
						></div>
					</a>

					<p class="text-sm text-zinc-500">{data.downloadCount.toLocaleString()} downloads</p>
				</div>

				<div class="grid gap-6 md:grid-cols-3">
					<div class="flex flex-col items-center rounded-lg border border-zinc-800 bg-black/20 p-4">
						<svg
							xmlns="http://www.w3.org/2000/svg"
							class="mb-2 h-6 w-6 text-purple-500"
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
						<h3 class="mb-1 font-semibold text-white">Anti-Cheat Safe</h3>
						<p class="text-center text-sm text-zinc-500">
							External overlay that doesn't modify game files
						</p>
					</div>

					<div class="flex flex-col items-center rounded-lg border border-zinc-800 bg-black/20 p-4">
						<svg
							xmlns="http://www.w3.org/2000/svg"
							class="mb-2 h-6 w-6 text-purple-500"
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
						<h3 class="mb-1 font-semibold text-white">Lightweight</h3>
						<p class="text-center text-sm text-zinc-500">Minimal impact on game performance</p>
					</div>

					<div class="flex flex-col items-center rounded-lg border border-zinc-800 bg-black/20 p-4">
						<svg
							xmlns="http://www.w3.org/2000/svg"
							class="mb-2 h-6 w-6 text-purple-500"
							fill="none"
							viewBox="0 0 24 24"
							stroke="currentColor"
						>
							<path
								stroke-linecap="round"
								stroke-linejoin="round"
								stroke-width="2"
								d="M8 7h12m0 0l-4-4m4 4l-4 4m0 6H4m0 0l4 4m-4-4l4-4"
							/>
						</svg>
						<h3 class="mb-1 font-semibold text-white">Regular Updates</h3>
						<p class="text-center text-sm text-zinc-500">Keeping pace with game patches</p>
					</div>
				</div>
			</div>
		</section>

		<!-- System Requirements Section -->
		<section class="mb-12">
			<div class="rounded-xl border border-zinc-800 bg-zinc-900/70 p-6">
				<h2 class="mb-4 flex items-center text-xl font-bold text-white">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-2 h-5 w-5 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M9 3v2m6-2v2M9 19v2m6-2v2M5 9H3m2 6H3m18-6h-2m2 6h-2M7 19h10a2 2 0 002-2V7a2 2 0 00-2-2H7a2 2 0 00-2 2v10a2 2 0 002 2zM9 9h6v6H9V9z"
						/>
					</svg>
					System Requirements
				</h2>

				<div class="grid gap-6 md:grid-cols-5">
					<div class="space-y-2 md:col-span-1">
						<p class="text-sm font-medium text-zinc-300">Operating System:</p>
						<p class="text-sm text-zinc-500">Windows 10/11 (64-bit)</p>
					</div>

					<div class="space-y-2 md:col-span-1">
						<p class="text-sm font-medium text-zinc-300">Processor:</p>
						<p class="text-sm text-zinc-500">Intel Core i3 or equivalent</p>
					</div>

					<div class="space-y-2 md:col-span-1">
						<p class="text-sm font-medium text-zinc-300">Memory:</p>
						<p class="text-sm text-zinc-500">2 GB RAM</p>
					</div>

					<div class="space-y-2 md:col-span-1">
						<p class="text-sm font-medium text-zinc-300">Storage:</p>
						<p class="text-sm text-zinc-500">100 MB available space</p>
					</div>

					<div class="space-y-2 md:col-span-1">
						<p class="text-sm font-medium text-zinc-300">Graphics:</p>
						<p class="text-sm text-zinc-500">DirectX 11 compatible</p>
					</div>
				</div>

				<div class="mt-4 rounded-lg bg-black/30 p-3">
					<p class="text-sm font-medium text-zinc-300">Additional Notes:</p>
					<p class="text-sm text-zinc-500">
						Must be run as administrator to properly detect and overlay with Phasmophobia game.
						Internet connection required for updates.
					</p>
				</div>
			</div>
		</section>

		<!-- Features Section -->
		<section class="mb-12">
			<div class="rounded-xl border border-zinc-800 bg-zinc-900/70 p-6">
				<h2 class="mb-6 flex items-center text-xl font-bold text-white">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-2 h-5 w-5 text-purple-500"
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
					Features
				</h2>

				<!-- Desktop Category Tabs -->
				<div class="mb-4 overflow-x-auto">
					<div class="flex space-x-1 border-b border-zinc-800">
						{#each featureCategories as category, index}
							<button
								class={`px-4 py-2 text-sm font-medium whitespace-nowrap transition ${activeCategoryIndex === index ? 'border-b-2 border-purple-500 text-white' : 'text-zinc-500 hover:text-zinc-300'}`}
								onclick={() => (activeCategoryIndex = index)}
							>
								{category.name}
							</button>
						{/each}
					</div>
				</div>

				<!-- Features Content -->
				<div class="mt-4">
					{#each featureCategories as category, categoryIndex}
						{#if categoryIndex === activeCategoryIndex}
							<div class="grid gap-4 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4">
								{#each category.features as feature}
									<div class="rounded-lg border border-zinc-800 bg-black/30 p-4">
										<h3 class="mb-2 text-base font-medium text-white">{feature.title}</h3>
										<p class="text-sm text-zinc-400">{feature.description}</p>
									</div>
								{/each}
							</div>
						{/if}
					{/each}
				</div>

				<!-- Feature Highlights -->
				<div class="mt-6 rounded-lg bg-black/30 p-4">
					<h3 class="mb-3 font-medium text-white">Additional Features:</h3>
					<div class="grid gap-2 sm:grid-cols-2 md:grid-cols-3">
						<div class="flex items-start">
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="mt-0.5 mr-2 h-4 w-4 flex-shrink-0 text-purple-500"
								viewBox="0 0 20 20"
								fill="currentColor"
							>
								<path
									fill-rule="evenodd"
									d="M16.707 5.293a1 1 0 010 1.414l-8 8a1 1 0 01-1.414 0l-4-4a1 1 0 011.414-1.414L8 12.586l7.293-7.293a1 1 0 011.414 0z"
									clip-rule="evenodd"
								/>
							</svg>
							<span class="text-sm text-zinc-400">Game log analysis</span>
						</div>
						<div class="flex items-start">
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="mt-0.5 mr-2 h-4 w-4 flex-shrink-0 text-purple-500"
								viewBox="0 0 20 20"
								fill="currentColor"
							>
								<path
									fill-rule="evenodd"
									d="M16.707 5.293a1 1 0 010 1.414l-8 8a1 1 0 01-1.414 0l-4-4a1 1 0 011.414-1.414L8 12.586l7.293-7.293a1 1 0 011.414 0z"
									clip-rule="evenodd"
								/>
							</svg>
							<span class="text-sm text-zinc-400">Weather condition effects</span>
						</div>
						<div class="flex items-start">
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="mt-0.5 mr-2 h-4 w-4 flex-shrink-0 text-purple-500"
								viewBox="0 0 20 20"
								fill="currentColor"
							>
								<path
									fill-rule="evenodd"
									d="M16.707 5.293a1 1 0 010 1.414l-8 8a1 1 0 01-1.414 0l-4-4a1 1 0 011.414-1.414L8 12.586l7.293-7.293a1 1 0 011.414 0z"
									clip-rule="evenodd"
								/>
							</svg>
							<span class="text-sm text-zinc-400">Team communication tools</span>
						</div>
						<div class="flex items-start">
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="mt-0.5 mr-2 h-4 w-4 flex-shrink-0 text-purple-500"
								viewBox="0 0 20 20"
								fill="currentColor"
							>
								<path
									fill-rule="evenodd"
									d="M16.707 5.293a1 1 0 010 1.414l-8 8a1 1 0 01-1.414 0l-4-4a1 1 0 011.414-1.414L8 12.586l7.293-7.293a1 1 0 011.414 0z"
									clip-rule="evenodd"
								/>
							</svg>
							<span class="text-sm text-zinc-400">Automatic game update detection</span>
						</div>
						<div class="flex items-start">
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="mt-0.5 mr-2 h-4 w-4 flex-shrink-0 text-purple-500"
								viewBox="0 0 20 20"
								fill="currentColor"
							>
								<path
									fill-rule="evenodd"
									d="M16.707 5.293a1 1 0 010 1.414l-8 8a1 1 0 01-1.414 0l-4-4a1 1 0 011.414-1.414L8 12.586l7.293-7.293a1 1 0 011.414 0z"
									clip-rule="evenodd"
								/>
							</svg>
							<span class="text-sm text-zinc-400">Performance optimization</span>
						</div>
						<div class="flex items-start">
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="mt-0.5 mr-2 h-4 w-4 flex-shrink-0 text-purple-500"
								viewBox="0 0 20 20"
								fill="currentColor"
							>
								<path
									fill-rule="evenodd"
									d="M16.707 5.293a1 1 0 010 1.414l-8 8a1 1 0 01-1.414 0l-4-4a1 1 0 011.414-1.414L8 12.586l7.293-7.293a1 1 0 011.414 0z"
									clip-rule="evenodd"
								/>
							</svg>
							<span class="text-sm text-zinc-400">Auto-save functionality</span>
						</div>
					</div>
				</div>
			</div>
		</section>

		<!-- News Section (formerly Release Notes) -->
		<section class="mb-12">
			<div class="rounded-xl border border-zinc-800 bg-zinc-900/70 p-6">
				<h2 class="mb-6 flex items-center text-xl font-bold text-white">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-2 h-5 w-5 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M9 5H7a2 2 0 00-2 2v12a2 2 0 002 2h10a2 2 0 002-2V7a2 2 0 00-2-2h-2M9 5a2 2 0 012-2h2a2 2 0 012 2"
						/>
					</svg>
					News & Updates
				</h2>

				{#if data.posts.length === 0}
					<div class="rounded-lg bg-black/30 p-4 text-center text-zinc-400">
						No news updates available yet.
					</div>
				{:else}
					<div class="space-y-4">
						{#each data.posts as post (post.id)}
							<div class="rounded-lg border border-zinc-800 bg-black/40">
								<button
									class="flex w-full cursor-pointer items-center justify-between p-4"
									onclick={() => togglePost(post.id)}
								>
									<div>
										<div class="flex items-center gap-2 text-left">
											<h3 class="font-medium text-white">{post.title}</h3>
											<span class="rounded-full bg-zinc-800 px-2 py-0.5 text-xs text-zinc-300">
												{post.type}
											</span>
										</div>
										<p class="text-left text-xs text-zinc-500">
											{new Date(post.createdAt!).toLocaleDateString()} • by {post.author.username}
										</p>
									</div>
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class={`h-5 w-5 text-zinc-500 transition-transform ${expandedPostId === post.id ? 'rotate-180' : ''}`}
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M19 9l-7 7-7-7"
										/>
									</svg>
								</button>

								{#if expandedPostId === post.id}
									<div class="border-t border-zinc-800 px-4 py-3">
										{#if post.content.includes('\n') || post.content.includes('- ')}
											<ul class="space-y-2 pl-1">
												{#each parseContent(post.content) as item}
													<li class="flex items-start">
														<svg
															xmlns="http://www.w3.org/2000/svg"
															class="mt-0.5 mr-2 h-4 w-4 flex-shrink-0 text-purple-500"
															viewBox="0 0 20 20"
															fill="currentColor"
														>
															<path
																fill-rule="evenodd"
																d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
																clip-rule="evenodd"
															/>
														</svg>
														<span class="text-sm text-zinc-400">{item}</span>
													</li>
												{/each}
											</ul>
										{:else}
											<p class="text-sm text-zinc-400">{post.content}</p>
										{/if}
									</div>
								{/if}
							</div>
						{/each}
					</div>
				{/if}

				{#if data.user?.role === 'administrator'}
					<div class="mt-4 flex justify-end">
						<a href="/admin/posts" class="text-sm text-purple-400 hover:text-purple-300">
							Manage Posts
						</a>
					</div>
				{/if}
			</div>
		</section>

		<!-- Download Section -->
		<section id="download" class="scroll-mt-20">
			<div class="rounded-xl border border-zinc-800 bg-zinc-900/70 p-6">
				<h2 class="mb-6 flex items-center text-xl font-bold text-white">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-2 h-5 w-5 text-purple-500"
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
					Download Asthmaphobia
				</h2>

				<div class="grid gap-6 md:grid-cols-2">
					<div class="rounded-lg border border-zinc-800 bg-black/40 p-5">
						<div class="flex items-start justify-between">
							<div>
								<h3 class="mb-1 font-medium text-white">Asthmaphobia v{data.currentVersion}</h3>
								<p class="mb-4 text-sm text-zinc-500">Stable Release • {data.releaseDate}</p>

								<div class="mb-4 text-xs text-zinc-600">
									<p>SHA-256: 8a2b5e9c7d3f6g1h0i4j5k6l7m8n9o0p1q2r3s4t5u6v7w8x9y0z</p>
								</div>
							</div>

							<span
								class="rounded-full bg-green-900/30 px-2 py-0.5 text-xs font-medium text-green-400"
							>
								Recommended
							</span>
						</div>

						<a
							href="#download-stable"
							class="flex w-full items-center justify-center rounded-lg bg-purple-700 px-4 py-2.5 text-sm font-medium text-white transition hover:bg-purple-600 focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black focus:outline-none"
						>
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="mr-2 h-4 w-4"
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
							Download (.zip)
						</a>
					</div>

					<div class="rounded-lg border border-zinc-800 bg-black/40 p-5">
						<div class="flex items-start justify-between">
							<div>
								<h3 class="mb-1 font-medium text-white">Asthmaphobia v1.3.3-beta</h3>
								<p class="mb-4 text-sm text-zinc-500">Beta Release • March 20, 2024</p>

								<div class="mb-4 text-xs text-zinc-600">
									<p>SHA-256: 7z6y5x4w3v2u1t0s9r8q7p6o5n4m3l2k1j0i9h8g7f6e5d4c3b2a</p>
								</div>
							</div>

							<span
								class="rounded-full bg-yellow-900/30 px-2 py-0.5 text-xs font-medium text-yellow-400"
							>
								Beta
							</span>
						</div>

						<a
							href="#download-beta"
							class="flex w-full items-center justify-center rounded-lg border border-purple-700 bg-transparent px-4 py-2.5 text-sm font-medium text-purple-400 transition hover:bg-purple-900/20 focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black focus:outline-none"
						>
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="mr-2 h-4 w-4"
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
							Download Beta (.zip)
						</a>
					</div>
				</div>

				<div class="mt-6 rounded-lg bg-purple-900/10 p-4 text-sm text-purple-300">
					<div class="flex">
						<svg
							xmlns="http://www.w3.org/2000/svg"
							class="mt-0.5 mr-3 h-5 w-5 flex-shrink-0"
							fill="none"
							viewBox="0 0 24 24"
							stroke="currentColor"
						>
							<path
								stroke-linecap="round"
								stroke-linejoin="round"
								stroke-width="2"
								d="M13 16h-1v-4h-1m1-4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
							/>
						</svg>
						<div>
							<p class="mb-1 font-medium">Installation Instructions</p>
							<ol class="ml-4 list-decimal space-y-1 text-purple-200">
								<li>Download the .zip file</li>
								<li>Extract all contents to a folder of your choice</li>
								<li>Run Asthmaphobia.exe as administrator</li>
								<li>Launch Phasmophobia and enjoy!</li>
							</ol>
						</div>
					</div>
				</div>
			</div>
		</section>
	</div>
</div>
