<script lang="ts">
	// Form state management
	let name = $state('');
	let email = $state('');
	let issueType = $state('technical');
	let message = $state('');
	let submitted = $state(false);
	let submitError = $state(false);

	// Common issues
	const commonIssues = [
		{
			title: 'Game Crashes on Launch',
			solution:
				'Run the application as administrator, disable overlay applications, and ensure your graphics drivers are up to date.'
		},
		{
			title: 'Features Not Working',
			solution:
				'Make sure the game is fully loaded before activating features. If using the latest version of Phasmophobia, check for an update to Asthmaphobia.'
		},
		{
			title: 'Detection Risk',
			solution:
				'Always close any streaming or recording software before using Asthmaphobia. Make sure to use the latest version with our stealth updates.'
		},
		{
			title: 'Key Bindings Not Working',
			solution:
				"Check that your key bindings don't conflict with the game's default controls. You can reset to default in the settings menu."
		}
	];

	// Handle form submission
	function handleSubmit() {
		if (!name || !email || !message) {
			submitError = true;
			return;
		}

		// Simulate API call delay
		setTimeout(() => {
			submitted = true;
			submitError = false;
		}, 1000);
	}
</script>

<svelte:head>
	<title>Support - Asthmaphobia</title>
	<meta name="description" content="Get help and support for Asthmaphobia cheat tool" />
</svelte:head>

<div class="min-h-screen bg-black">
	<div class="relative">
		<div
			class="absolute inset-0 bg-gradient-to-b from-purple-900/20 via-transparent to-transparent opacity-60"
		></div>
		<div class="relative z-10 container mx-auto max-w-6xl px-4 py-8">
			<!-- Header -->
			<section>
				<div class="mt-8 mb-12 text-center">
					<h1 class="mb-4 text-4xl font-bold text-white md:text-5xl">
						<span class="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent"
							>Support Center</span
						>
					</h1>
					<p class="mx-auto max-w-2xl text-zinc-300">
						Having issues with Asthmaphobia? Our dedicated support team is here to help you resolve
						any problems and get back to dominating Phasmophobia.
					</p>
				</div>
			</section>

			<!-- Support Options -->
			<section>
				<div class="mb-16 grid gap-6 md:grid-cols-2">
					<div
						class="group rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 text-center backdrop-blur-sm transition-all hover:border-purple-600/30"
					>
						<div
							class="mx-auto mb-4 flex h-16 w-16 items-center justify-center rounded-lg bg-gradient-to-br from-purple-900/40 to-indigo-900/40"
						>
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="h-8 w-8 text-purple-400"
								fill="none"
								viewBox="0 0 24 24"
								stroke="currentColor"
							>
								<path
									stroke-linecap="round"
									stroke-linejoin="round"
									stroke-width="2"
									d="M3 8l7.89 5.26a2 2 0 002.22 0L21 8M5 19h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v10a2 2 0 002 2z"
								/>
							</svg>
						</div>
						<h3 class="mb-2 text-xl font-medium text-white">Email Support</h3>
						<p class="mb-4 text-sm text-zinc-400">
							Submit a detailed inquiry to our technical team for complex issues requiring
							investigation.
						</p>
						<a
							href="mailto:support@asthmaphobia.xyz"
							class="inline-flex items-center rounded-lg bg-gradient-to-r from-purple-600 to-indigo-600 px-4 py-2 text-sm font-medium text-white transition-colors hover:from-purple-500 hover:to-indigo-500"
						>
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
									d="M3 8l7.89 5.26a2 2 0 002.22 0L21 8M5 19h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v10a2 2 0 002 2z"
								/>
							</svg>
							Email Us
						</a>
					</div>

					<div
						class="group rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 text-center backdrop-blur-sm transition-all hover:border-purple-600/30"
					>
						<div
							class="mx-auto mb-4 flex h-16 w-16 items-center justify-center rounded-lg bg-gradient-to-br from-purple-900/40 to-indigo-900/40"
						>
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="h-8 w-8 text-purple-400"
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
						</div>
						<h3 class="mb-2 text-xl font-medium text-white">Frequently Asked Questions</h3>
						<p class="mb-4 text-sm text-zinc-400">
							Find answers to common questions about Asthmaphobia in our comprehensive FAQ section.
						</p>
						<a
							href="/faq"
							class="inline-flex items-center rounded-lg border border-purple-700/50 bg-purple-900/10 px-4 py-2 text-sm font-medium text-purple-300 transition-colors hover:bg-purple-900/30"
						>
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
									d="M8.228 9c.549-1.165 2.03-2 3.772-2 2.21 0 4 1.343 4 3 0 1.4-1.278 2.575-3.006 2.907-.542.104-.994.54-.994 1.093m0 3h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
								/>
							</svg>
							View FAQ
						</a>
					</div>
				</div>
			</section>

			<!-- Troubleshooting Section -->
			<section>
				<div class="mb-16">
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
								d="M10 19l-7-7m0 0l7-7m-7 7h18"
							/>
						</svg>
						Common Issues & Solutions
					</h2>

					<div class="grid gap-4 md:grid-cols-2">
						{#each commonIssues as issue, i}
							<div
								class="rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 backdrop-blur-sm transition-all hover:border-purple-600/30"
							>
								<h3 class="mb-2 text-lg font-medium text-white">{issue.title}</h3>
								<p class="text-zinc-400">{issue.solution}</p>
							</div>
						{/each}
					</div>
				</div>
			</section>

			<!-- Support Ticket Form -->
			<section>
				<div class="relative overflow-hidden rounded-3xl border border-zinc-800/40 bg-zinc-900/70">
					<div
						class="absolute inset-0 bg-gradient-to-r from-purple-900/20 to-blue-900/20 opacity-30"
					></div>
					<div class="absolute -inset-[500px] -z-10">
						<div
							class="absolute top-1/3 left-1/3 h-[600px] w-[600px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-purple-500/20 blur-[100px]"
						></div>
					</div>

					<div class="relative z-10 p-8 md:p-10">
						<h2 class="mb-8 text-center text-3xl font-bold text-white">Submit a Support Ticket</h2>

						{#if submitted}
							<div class="mx-auto max-w-lg rounded-xl bg-green-900/20 p-6 text-center">
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="mx-auto mb-4 h-16 w-16 text-green-400"
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
								<h3 class="mb-2 text-xl font-medium text-white">Ticket Submitted Successfully</h3>
								<p class="text-zinc-300">
									Thank you for contacting us. Our support team will review your issue and respond
									as soon as possible. Please check your email for updates.
								</p>
								<button
									class="mt-6 rounded-lg bg-gradient-to-r from-purple-600 to-indigo-600 px-6 py-2 font-medium text-white hover:from-purple-500 hover:to-indigo-500"
									onclick={() => (submitted = false)}
								>
									Submit Another Ticket
								</button>
							</div>
						{:else}
							<form
								class="mx-auto max-w-2xl space-y-6"
								onsubmit={(e: any) => e.preventDefault() || handleSubmit()}
							>
								{#if submitError}
									<div class="rounded-lg bg-red-900/20 p-4 text-red-200">
										<p>Please fill out all required fields.</p>
									</div>
								{/if}

								<div class="grid gap-6 md:grid-cols-2">
									<div>
										<label for="name" class="mb-2 block text-sm font-medium text-zinc-300"
											>Your Name</label
										>
										<input
											type="text"
											id="name"
											bind:value={name}
											class="w-full rounded-lg border border-zinc-700 bg-zinc-800/50 p-2.5 text-white placeholder-zinc-400 focus:border-purple-500 focus:ring-purple-500"
											placeholder="John Doe"
											required
										/>
									</div>
									<div>
										<label for="email" class="mb-2 block text-sm font-medium text-zinc-300"
											>Your Email</label
										>
										<input
											type="email"
											id="email"
											bind:value={email}
											class="w-full rounded-lg border border-zinc-700 bg-zinc-800/50 p-2.5 text-white placeholder-zinc-400 focus:border-purple-500 focus:ring-purple-500"
											placeholder="name@example.com"
											required
										/>
									</div>
								</div>

								<div>
									<label for="issue" class="mb-2 block text-sm font-medium text-zinc-300"
										>Issue Type</label
									>
									<select
										id="issue"
										bind:value={issueType}
										class="w-full rounded-lg border border-zinc-700 bg-zinc-800/50 p-2.5 text-white placeholder-zinc-400 hover:cursor-pointer focus:border-purple-500 focus:ring-purple-500"
									>
										<option value="technical">Technical Issue</option>
										<option value="feature">Feature Request</option>
										<option value="other">Other</option>
									</select>
								</div>

								<div>
									<label for="message" class="mb-2 block text-sm font-medium text-zinc-300"
										>Your Message</label
									>
									<textarea
										id="message"
										bind:value={message}
										rows="6"
										class="w-full rounded-lg border border-zinc-700 bg-zinc-800/50 p-2.5 text-white placeholder-zinc-400 focus:border-purple-500 focus:ring-purple-500"
										placeholder="Describe your issue in detail. Include any error messages, your system specifications, and steps to reproduce the problem."
										required
									></textarea>
								</div>

								<div class="flex items-center">
									<input
										id="privacy"
										type="checkbox"
										value=""
										class="h-4 w-4 rounded border-zinc-600 bg-zinc-700 text-purple-600 hover:cursor-pointer focus:ring-2 focus:ring-purple-500"
										required
									/>
									<label for="privacy" class="ml-2 text-sm text-zinc-400">
										I agree that my information will be processed according to the <a
											href="/privacy"
											class="text-purple-400 underline hover:text-purple-300">Privacy Policy</a
										>.
									</label>
								</div>

								<button
									type="submit"
									class="w-full rounded-lg bg-gradient-to-r from-purple-600 to-indigo-600 px-5 py-3 text-center font-medium text-white hover:cursor-pointer hover:from-purple-500 hover:to-indigo-500 focus:ring-4 focus:ring-purple-800 focus:outline-none"
								>
									Submit Ticket
								</button>
							</form>
						{/if}
					</div>
				</div>
			</section>
		</div>
	</div>
</div>
