<script lang="ts">
	import { enhance } from '$app/forms';
	import type { ActionData } from './$types';
	import type { PageServerData } from './$types';

	let { form, data }: { form: ActionData; data: PageServerData } = $props();
	let showCurrentPassword = $state(false);
	let showPassword = $state(false);
	let showConfirmPassword = $state(false);

	const togglePasswordVisibility = (field: 'current' | 'password' | 'confirm') => {
		if (field === 'current') showCurrentPassword = !showCurrentPassword;
		else if (field === 'password') showPassword = !showPassword;
		else showConfirmPassword = !showConfirmPassword;
	};
</script>

<div class="mx-auto max-w-4xl px-4 py-8">
	<div class="flex flex-col gap-6 md:flex-row">
		<!-- Profile Sidebar -->
		<div class="md:w-1/3">
			<div
				class="flex flex-col items-center rounded-xl border border-zinc-800 bg-zinc-900 p-6 shadow-lg"
			>
				<div
					class="mb-4 flex h-32 w-32 items-center justify-center overflow-hidden rounded-full border-2 border-purple-600 bg-black"
				>
					<span class="text-4xl font-bold text-purple-500"
						>{data.user.username.charAt(0).toUpperCase()}</span
					>
				</div>
				<h1 class="mb-1 text-2xl font-bold text-white">{data.user.username}</h1>
				<p class="mb-4 text-sm text-zinc-400">{data.user.email || 'No email set'}</p>
				<div class="mb-4 w-full rounded-lg bg-black/40 p-3">
					<p class="mb-1 text-xs text-zinc-500">User ID</p>
					<p class="font-mono text-sm break-all text-zinc-400">{data.user.id}</p>
				</div>
				<div class="mt-2 w-full text-center">
					<form method="POST" action="?/logout">
						<button type="submit" class="text-sm font-medium text-red-500 hover:text-red-400">
							Sign out
						</button>
					</form>
				</div>
			</div>
		</div>

		<!-- Profile Content -->
		<div class="md:w-2/3">
			<div class="rounded-xl border border-zinc-800 bg-zinc-900 p-6 shadow-lg">
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
							d="M16 7a4 4 0 11-8 0 4 4 0 018 0zM12 14a7 7 0 00-7 7h14a7 7 0 00-7-7z"
						/>
					</svg>
					Edit Profile
				</h2>

				{#if form?.message}
					<div
						class="mb-6 flex items-start rounded border-l-4 border-red-600 bg-red-900/20 p-3 text-red-400"
					>
						<svg
							xmlns="http://www.w3.org/2000/svg"
							class="mt-0.5 mr-2 h-5 w-5 flex-shrink-0"
							fill="none"
							viewBox="0 0 24 24"
							stroke="currentColor"
						>
							<path
								stroke-linecap="round"
								stroke-linejoin="round"
								stroke-width="2"
								d="M12 8v4m0 4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
							/>
						</svg>
						<span>{form.message}</span>
					</div>
				{/if}

				<form method="POST" action="?/update" use:enhance class="space-y-5">
					<div class="space-y-5">
						<h3 class="mb-3 border-b border-zinc-800 pb-2 text-sm font-medium text-zinc-300">
							Account Information
						</h3>

						<div>
							<label for="email" class="mb-1 block text-sm font-medium text-zinc-300">
								Email address <span class="text-purple-500">*</span>
							</label>
							<div class="relative">
								<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="h-4 w-4 text-zinc-600"
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
								<input
									name="email"
									id="email"
									type="email"
									value={data.user.email || ''}
									class="w-full rounded-lg border border-zinc-800 bg-black py-2.5 pr-3 pl-10 text-zinc-200 focus:border-purple-600 focus:ring-1 focus:ring-purple-600 focus:outline-none"
									required
								/>
							</div>
						</div>

						<div>
							<label for="username" class="mb-1 block text-sm font-medium text-zinc-300">
								Username <span class="text-purple-500">*</span>
							</label>
							<div class="relative">
								<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="h-4 w-4 text-zinc-600"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M16 7a4 4 0 11-8 0 4 4 0 018 0zM12 14a7 7 0 00-7 7h14a7 7 0 00-7-7z"
										/>
									</svg>
								</div>
								<input
									name="username"
									id="username"
									type="text"
									value={data.user.username}
									class="w-full rounded-lg border border-zinc-800 bg-black py-2.5 pr-3 pl-10 text-zinc-200 focus:border-purple-600 focus:ring-1 focus:ring-purple-600 focus:outline-none"
									required
								/>
							</div>
						</div>
					</div>

					<div class="space-y-5 pt-2">
						<h3 class="mb-3 border-b border-zinc-800 pb-2 text-sm font-medium text-zinc-300">
							Change Password
						</h3>

						<div>
							<label for="current-password" class="mb-1 block text-sm font-medium text-zinc-300"
								>Current Password</label
							>
							<div class="relative">
								<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="h-4 w-4 text-zinc-600"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M12 15v2m-6 4h12a2 2 0 002-2v-6a2 2 0 00-2-2H6a2 2 0 00-2 2v6a2 2 0 002 2zm10-10V7a4 4 0 00-8 0v4h8z"
										/>
									</svg>
								</div>
								<input
									name="current-password"
									id="current-password"
									type={showCurrentPassword ? 'text' : 'password'}
									class="w-full rounded-lg border border-zinc-800 bg-black py-2.5 pr-10 pl-10 text-zinc-200 focus:border-purple-600 focus:ring-1 focus:ring-purple-600 focus:outline-none"
									placeholder="Enter current password"
								/>
								<button
									type="button"
									class="absolute inset-y-0 right-0 flex items-center pr-3 text-zinc-500 hover:text-zinc-300"
									onclick={() => togglePasswordVisibility('current')}
								>
									{#if showCurrentPassword}
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
												d="M13.875 18.825A10.05 10.05 0 0112 19c-4.478 0-8.268-2.943-9.543-7a9.97 9.97 0 011.563-3.029m5.858.908a3 3 0 114.243 4.243M9.878 9.878l4.242 4.242M9.88 9.88l-3.29-3.29m7.532 7.532l3.29 3.29M3 3l3.59 3.59m0 0A9.953 9.953 0 0112 5c4.478 0 8.268 2.943 9.543 7a10.025 10.025 0 01-4.132 5.411m0 0L21 21"
											/>
										</svg>
									{:else}
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
												d="M15 12a3 3 0 11-6 0 3 3 0 016 0z"
											/>
											<path
												stroke-linecap="round"
												stroke-linejoin="round"
												stroke-width="2"
												d="M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z"
											/>
										</svg>
									{/if}
								</button>
							</div>
							<p class="mt-1 text-xs text-zinc-600">Required only if changing your password</p>
						</div>

						<div>
							<label for="password" class="mb-1 block text-sm font-medium text-zinc-300"
								>New Password</label
							>
							<div class="relative">
								<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="h-4 w-4 text-zinc-600"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M12 15v2m-6 4h12a2 2 0 002-2v-6a2 2 0 00-2-2H6a2 2 0 00-2 2v6a2 2 0 002 2zm10-10V7a4 4 0 00-8 0v4h8z"
										/>
									</svg>
								</div>
								<input
									name="password"
									id="password"
									type={showPassword ? 'text' : 'password'}
									class="w-full rounded-lg border border-zinc-800 bg-black py-2.5 pr-10 pl-10 text-zinc-200 focus:border-purple-600 focus:ring-1 focus:ring-purple-600 focus:outline-none"
									placeholder="Enter new password"
								/>
								<button
									type="button"
									class="absolute inset-y-0 right-0 flex items-center pr-3 text-zinc-500 hover:text-zinc-300"
									onclick={() => togglePasswordVisibility('password')}
								>
									{#if showPassword}
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
												d="M13.875 18.825A10.05 10.05 0 0112 19c-4.478 0-8.268-2.943-9.543-7a9.97 9.97 0 011.563-3.029m5.858.908a3 3 0 114.243 4.243M9.878 9.878l4.242 4.242M9.88 9.88l-3.29-3.29m7.532 7.532l3.29 3.29M3 3l3.59 3.59m0 0A9.953 9.953 0 0112 5c4.478 0 8.268 2.943 9.543 7a10.025 10.025 0 01-4.132 5.411m0 0L21 21"
											/>
										</svg>
									{:else}
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
												d="M15 12a3 3 0 11-6 0 3 3 0 016 0z"
											/>
											<path
												stroke-linecap="round"
												stroke-linejoin="round"
												stroke-width="2"
												d="M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z"
											/>
										</svg>
									{/if}
								</button>
							</div>
							<p class="mt-1 text-xs text-zinc-600">Leave blank to keep your current password</p>
						</div>

						<div>
							<label for="confirm-password" class="mb-1 block text-sm font-medium text-zinc-300"
								>Confirm New Password</label
							>
							<div class="relative">
								<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="h-4 w-4 text-zinc-600"
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
								</div>
								<input
									name="confirm-password"
									id="confirm-password"
									type={showConfirmPassword ? 'text' : 'password'}
									class="w-full rounded-lg border border-zinc-800 bg-black py-2.5 pr-10 pl-10 text-zinc-200 focus:border-purple-600 focus:ring-1 focus:ring-purple-600 focus:outline-none"
									placeholder="Confirm new password"
								/>
								<button
									type="button"
									class="absolute inset-y-0 right-0 flex items-center pr-3 text-zinc-500 hover:text-zinc-300"
									onclick={() => togglePasswordVisibility('confirm')}
								>
									{#if showConfirmPassword}
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
												d="M13.875 18.825A10.05 10.05 0 0112 19c-4.478 0-8.268-2.943-9.543-7a9.97 9.97 0 011.563-3.029m5.858.908a3 3 0 114.243 4.243M9.878 9.878l4.242 4.242M9.88 9.88l-3.29-3.29m7.532 7.532l3.29 3.29M3 3l3.59 3.59m0 0A9.953 9.953 0 0112 5c4.478 0 8.268 2.943 9.543 7a10.025 10.025 0 01-4.132 5.411m0 0L21 21"
											/>
										</svg>
									{:else}
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
												d="M15 12a3 3 0 11-6 0 3 3 0 016 0z"
											/>
											<path
												stroke-linecap="round"
												stroke-linejoin="round"
												stroke-width="2"
												d="M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z"
											/>
										</svg>
									{/if}
								</button>
							</div>
						</div>

						<!-- Hidden user ID field -->
						<input type="hidden" name="user-id" value={data.user.id} />
					</div>

					<div class="pt-4">
						<button
							type="submit"
							class="flex w-full items-center justify-center rounded-lg bg-purple-700 px-4 py-2.5 text-sm font-semibold text-white shadow-md transition-colors hover:bg-purple-600 focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black focus:outline-none"
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
									d="M5 13l4 4L19 7"
								/>
							</svg>
							Save Changes
						</button>
					</div>
				</form>
			</div>
		</div>
	</div>
</div>
