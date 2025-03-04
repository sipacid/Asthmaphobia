<script lang="ts">
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { type User, type UserLogin } from '$lib/server/db/schema';

	let { userId, onClose } = $props();

	let user: User | null = $state(null);
	let userLogins: UserLogin[] = $state([]);
	let loading: boolean = $state(true);
	let error: string | null = $state(null);

	// Fetch user details on mount
	onMount(async () => {
		loading = true;
		error = null;

		try {
			// Create form data for the request
			const formData = new FormData();
			formData.append('userId', userId);

			// Fetch user details
			const response = await fetch('?/getUserDetails', {
				method: 'POST',
				body: formData
			});

			const result = await response.json();
			console.log('API response:', result); // Debug response
			console.log('data', result.data);

			if (result.type === 'success') {
				user = result.data.user;
				userLogins = result.data.userLogins || [];
			} else {
				error = result.error || 'Failed to fetch user details';
			}
		} catch (err) {
			console.error('Error fetching user details:', err);
			error = 'Failed to load user details. Please try again.';
		} finally {
			loading = false;
		}
	});

	function handleKeydown(event: KeyboardEvent) {
		if (event.key === 'Escape') {
			onClose();
		}
	}

	function handleBackdropClick(event: MouseEvent) {
		if (event.target === event.currentTarget) {
			onClose();
		}
	}
</script>

<svelte:window on:keydown={handleKeydown} />

<!-- svelte-ignore a11y_no_noninteractive_element_interactions -->
<div
	role="dialog"
	aria-modal="true"
	class="fixed inset-0 z-50 flex items-center justify-center bg-black/50 p-4"
	onclick={handleBackdropClick}
	onkeydown={(e) => e.key === 'Escape' && onClose()}
	transition:fade={{ duration: 200 }}
>
	<div
		class="w-full max-w-3xl rounded-lg border border-zinc-700 bg-zinc-900 shadow-xl"
		transition:fade={{ duration: 150 }}
	>
		<!-- Modal Header -->
		<div class="flex items-center justify-between border-b border-zinc-800 p-4">
			<h3 class="text-xl font-medium text-white">User Details</h3>
			<button
				type="button"
				onclick={onClose}
				aria-label="Close modal"
				class="ml-auto rounded-lg p-1.5 text-zinc-400 hover:bg-zinc-800 hover:text-white"
			>
				<svg class="h-5 w-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
					<path
						stroke-linecap="round"
						stroke-linejoin="round"
						stroke-width="2"
						d="M6 18L18 6M6 6l12 12"
					/>
				</svg>
			</button>
		</div>

		<!-- Modal Body -->
		<div class="p-6">
			{#if loading}
				<div class="flex justify-center py-8">
					<div
						class="h-8 w-8 animate-spin rounded-full border-4 border-zinc-600 border-t-purple-500"
					></div>
				</div>
			{:else if error}
				<div class="rounded-md bg-red-900/20 p-4 text-center text-red-400">{error}</div>
			{:else if user}
				<!-- User Info Section -->
				<div class="mb-6">
					<h4 class="mb-3 text-lg font-semibold text-white">User Information</h4>
					<div class="grid grid-cols-1 gap-4 md:grid-cols-2">
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">Username</p>
							<p class="text-white">{user.username || 'N/A'}</p>
						</div>
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">Email</p>
							<p class="text-white">{user.email || 'N/A'}</p>
						</div>
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">User ID</p>
							<p class="text-white">{user.id || 'N/A'}</p>
						</div>
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">Role</p>
							<p>
								<span
									class={`rounded-full px-2.5 py-0.5 text-xs font-medium ${user.role === 'administrator' ? 'bg-purple-900/20 text-purple-400' : 'bg-blue-900/20 text-blue-400'}`}
								>
									{user.role === 'administrator' ? 'Administrator' : 'Standard User'}
								</span>
							</p>
						</div>
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">Created At</p>
							<p class="text-white">{new Date(user.createdAt!).toLocaleString()}</p>
						</div>
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">Updated At</p>
							<p class="text-white">{new Date(user.updatedAt!).toLocaleString()}</p>
						</div>
					</div>
				</div>

				<!-- User Logins Section -->
				<div>
					<h4 class="mb-3 text-lg font-semibold text-white">Login History</h4>
					{#if !userLogins || userLogins.length === 0}
						<p class="rounded-md bg-zinc-800/50 p-4 text-center text-zinc-400">
							No login history available
						</p>
					{:else}
						<div class="max-h-64 overflow-y-auto rounded-lg border border-zinc-800">
							<table class="w-full table-auto">
								<thead>
									<tr class="border-b border-zinc-800 text-left">
										<th class="px-4 py-2 text-sm font-medium text-zinc-400">Date</th>
										<th class="px-4 py-2 text-sm font-medium text-zinc-400">IP Address</th>
										<th class="px-4 py-2 text-sm font-medium text-zinc-400">User Agent</th>
										<th class="px-4 py-2 text-sm font-medium text-zinc-400">Status</th>
									</tr>
								</thead>
								<tbody>
									{#each userLogins as login (login?.id || Math.random().toString())}
										{#if login}
											<tr class="border-b border-zinc-800">
												<td class="px-4 py-2 text-sm text-zinc-300"
													>{new Date(login.createdAt!).toLocaleString()}</td
												>
												<td class="px-4 py-2 text-sm text-zinc-300"
													>{login.ipAddress || 'Unknown'}</td
												>
												<td class="max-w-[200px] truncate px-4 py-2 text-sm text-zinc-300">
													{login.userAgent || 'Unknown'}
												</td>
												<td class="px-4 py-2">
													<span
														class={`inline-block rounded px-2 py-1 text-xs ${login.success ? 'bg-green-900/20 text-green-400' : 'bg-red-900/20 text-red-400'}`}
													>
														{login.success ? 'Success' : 'Failed'}
													</span>
												</td>
											</tr>
										{/if}
									{/each}
								</tbody>
							</table>
						</div>
					{/if}
				</div>
			{:else}
				<div class="rounded-md bg-red-900/20 p-4 text-center text-red-400">
					No user data available
				</div>
			{/if}
		</div>

		<!-- Modal Footer -->
		<div class="flex justify-end border-t border-zinc-800 p-4">
			<button
				type="button"
				onclick={onClose}
				class="rounded-lg bg-zinc-800 px-4 py-2 text-sm text-white hover:bg-zinc-700"
			>
				Close
			</button>
		</div>
	</div>
</div>
