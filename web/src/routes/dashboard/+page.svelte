<script lang="ts">
	import type { PageServerData } from './$types';

	let { data }: { data: PageServerData } = $props();

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
		<!-- Status Section -->
		<section class="mb-8">
			<div class="rounded-xl border border-zinc-800 bg-zinc-900/70 p-6 shadow-md">
				<div class="flex flex-col md:flex-row md:items-center md:justify-between">
					<div class="mb-4 md:mb-0">
						<h1 class="text-2xl font-bold text-white">Asthmaphobia</h1>
						<p class="text-zinc-400">
							Current version: <span class="text-purple-400">v{data.currentVersion}</span>
						</p>
					</div>

					<div class="flex flex-col gap-4 sm:flex-row">
						<div class="rounded-lg border border-zinc-800 bg-black/30 px-4 py-2 text-center">
							<p class="text-xs text-zinc-500">Game Support</p>
							<p class="text-sm font-medium text-zinc-300">{data.supportedGameVersion}</p>
						</div>

						<div class="rounded-lg border border-zinc-800 bg-black/30 px-4 py-2 text-center">
							<p class="text-xs text-zinc-500">Last Updated</p>
							<p class="text-sm font-medium text-zinc-300">{data.releaseDate}</p>
						</div>

						<a
							href="#download"
							class="flex items-center justify-center gap-2 rounded-lg bg-purple-700 px-4 py-2 font-medium text-white transition hover:bg-purple-600 focus:ring-2 focus:ring-purple-500 focus:outline-none"
						>
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="h-4 w-4"
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
							Download
						</a>
					</div>
				</div>
			</div>
		</section>

		<!-- System Requirements Section -->
		<section class="mb-8">
			<div class="rounded-xl border border-zinc-800 bg-zinc-900/70 p-6 shadow-md">
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
					<p class="text-sm font-medium text-zinc-300">Important:</p>
					<p class="text-sm text-zinc-500">
						Must be run as administrator to properly detect and overlay with Phasmophobia game.
						Internet connection required for updates.
					</p>
				</div>
			</div>
		</section>

		<!-- News & Updates Section -->
		<section class="mb-8">
			<div class="rounded-xl border border-zinc-800 bg-zinc-900/70 p-6 shadow-md">
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
							<div
								class="rounded-lg border border-zinc-800 bg-black/40 transition-all hover:border-zinc-700"
							>
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
						<a
							href="/admin/posts"
							class="flex items-center gap-1.5 text-sm text-purple-400 hover:text-purple-300"
						>
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="h-4 w-4"
								fill="none"
								viewBox="0 0 24 24"
								stroke="currentColor"
							>
								<path
									stroke-linecap="round"
									stroke-linejoin="round"
									stroke-width="2"
									d="M11 5H6a2 2 0 00-2 2v11a2 2 0 002 2h11a2 2 0 002-2v-5m-1.414-9.414a2 2 0 112.828 2.828L11.828 15H9v-2.828l8.586-8.586z"
								/>
							</svg>
							Manage Posts
						</a>
					</div>
				{/if}
			</div>
		</section>

		<!-- Download Section -->
		<section id="download" class="scroll-mt-20">
			<div class="rounded-xl border border-zinc-800 bg-zinc-900/70 p-6 shadow-md">
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
					Available Downloads
				</h2>

				<div class="grid gap-6 md:grid-cols-2">
					<div
						class="rounded-lg border border-zinc-800 bg-black/40 p-5 transition hover:border-zinc-700"
					>
						<div class="flex items-start justify-between">
							<div>
								<div class="flex items-center gap-2">
									<h3 class="font-medium text-white">Asthmaphobia v{data.currentVersion}</h3>
									<span
										class="rounded-full bg-green-900/30 px-2 py-0.5 text-xs font-medium text-green-400"
									>
										Stable
									</span>
								</div>
								<p class="mb-4 text-sm text-zinc-500">Released: {data.releaseDate}</p>

								<div class="mb-4 text-xs text-zinc-600">
									<p>SHA-256: 8a2b5e9c7d3f6g1h0i4j5k6l7m8n9o0p1q2r3s4t5u6v7w8x9y0z</p>
								</div>
							</div>
						</div>

						<div class="flex gap-3">
							<a
								href="#download-stable"
								class="flex flex-1 items-center justify-center rounded-lg bg-purple-700 px-4 py-2.5 text-sm font-medium text-white transition hover:bg-purple-600 focus:ring-2 focus:ring-purple-500 focus:outline-none"
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

							<a
								href="#changelog"
								class="flex items-center justify-center rounded-lg border border-zinc-700 px-3 py-2.5 text-sm font-medium text-zinc-400 transition hover:bg-zinc-800 hover:text-zinc-300 focus:ring-1 focus:ring-zinc-500 focus:outline-none"
							>
								Changelog
							</a>
						</div>
					</div>

					<div
						class="rounded-lg border border-zinc-800 bg-black/40 p-5 transition hover:border-zinc-700"
					>
						<div class="flex items-start justify-between">
							<div>
								<div class="flex items-center gap-2">
									<h3 class="font-medium text-white">Asthmaphobia v1.3.3-beta</h3>
									<span
										class="rounded-full bg-yellow-900/30 px-2 py-0.5 text-xs font-medium text-yellow-400"
									>
										Beta
									</span>
								</div>
								<p class="mb-4 text-sm text-zinc-500">Released: March 20, 2024</p>

								<div class="mb-4 text-xs text-zinc-600">
									<p>SHA-256: 7z6y5x4w3v2u1t0s9r8q7p6o5n4m3l2k1j0i9h8g7f6e5d4c3b2a</p>
								</div>
							</div>
						</div>

						<div class="flex gap-3">
							<a
								href="#download-beta"
								class="flex flex-1 items-center justify-center rounded-lg border border-purple-700 bg-transparent px-4 py-2.5 text-sm font-medium text-purple-400 transition hover:bg-purple-900/20 focus:ring-2 focus:ring-purple-500 focus:outline-none"
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

							<a
								href="#beta-changelog"
								class="flex items-center justify-center rounded-lg border border-zinc-700 px-3 py-2.5 text-sm font-medium text-zinc-400 transition hover:bg-zinc-800 hover:text-zinc-300 focus:ring-1 focus:ring-zinc-500 focus:outline-none"
							>
								Changelog
							</a>
						</div>
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

				<div class="mt-4 rounded-lg bg-red-900/10 p-4 text-sm text-red-300">
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
								d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"
							/>
						</svg>
						<div>
							<p class="mb-1 font-medium">Important Security Notice</p>
							<p class="text-red-200">
								Always verify download hashes before running. Only download from this official
								website. Third-party sources may contain malware.
							</p>
						</div>
					</div>
				</div>
			</div>
		</section>
	</div>
</div>
