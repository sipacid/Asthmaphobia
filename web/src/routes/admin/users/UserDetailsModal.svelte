<script lang="ts">
	import { enhance } from '$app/forms';
	import { fade } from 'svelte/transition';
	import type { ActionResult, SubmitFunction } from '@sveltejs/kit';

	// Define proper types for the user data
	interface UserData {
		id: string;
		username: string;
		email: string;
		role: string;
		createdAt?: string;
		updatedAt?: string;
	}

	interface LoginRecord {
		id: string;
		userId: string;
		ipAddress: string | null;
		userAgent: string | null;
		success: boolean;
		createdAt?: string;
	}

	export let userId: string;
	export let onClose: () => void;

	// Define state with proper types
	let loading = true;
	let error: string | null = null;
	let userData: UserData | null = null;
	let loginHistory: LoginRecord[] = [];

	// Enhanced form submission handler with proper typing
	const handleEnhance: SubmitFunction = () => {
		loading = true;
		error = null;

		return async ({ result }) => {
			handleResult(result);
		};
	};

	// Separate function to handle the form result
	function handleResult(result: ActionResult) {
		loading = false;

		if (result.type === 'success') {
			const data = result.data;

			if (data.success && data.user) {
				userData = data.user as UserData;
				loginHistory = (data.userLogins || []) as LoginRecord[];
			} else {
				error = 'Invalid response format';
				console.error('Unexpected response structure:', data);
			}
		} else if (result.type === 'failure') {
			error = result.data?.error || 'An error occurred while fetching user data';
		} else {
			error = 'Unknown response type';
		}
	}

	// More robust auto-submit function
	function autoSubmit(node: HTMLFormElement) {
		const submitForm = () => {
			try {
				node.requestSubmit();
			} catch (err) {
				console.error('Error auto-submitting form:', err);
				error = 'Failed to load user details automatically';
				loading = false;
			}
		};

		// Use setTimeout for better browser compatibility than requestAnimationFrame
		setTimeout(submitForm, 0);

		return {
			destroy() {} // Cleanup function (empty in this case)
		};
	}

	// Format date with proper fallback
	function formatDate(dateString?: string): string {
		if (!dateString) return 'N/A';

		try {
			return new Date(dateString).toLocaleString();
		} catch (err) {
			console.error('Invalid date format:', dateString, err);
			return 'Invalid Date';
		}
	}

	// Memoize role class to avoid recalculation
	$: roleClass =
		userData?.role === 'administrator'
			? 'bg-purple-900/20 text-purple-400'
			: 'bg-blue-900/20 text-blue-400';

	$: roleLabel = userData?.role === 'administrator' ? 'Administrator' : 'Standard User';
</script>

<svelte:window on:keydown={(e) => e.key === 'Escape' && onClose()} />

<!-- svelte-ignore a11y_click_events_have_key_events -->
<!-- svelte-ignore a11y_no_noninteractive_element_interactions -->
<div
	class="fixed inset-0 z-50 flex items-center justify-center overflow-y-auto bg-black/50 p-4"
	onclick={() => onClose()}
	transition:fade={{ duration: 200 }}
	role="dialog"
	aria-modal="true"
	aria-labelledby="modal-title"
>
	<div
		class="w-full max-w-3xl rounded-lg border border-zinc-700 bg-zinc-900 shadow-xl"
		transition:fade={{ duration: 150 }}
	>
		<!-- Modal Header -->
		<div class="flex items-center justify-between border-b border-zinc-800 p-4">
			<h3 id="modal-title" class="text-xl font-medium text-white">User Details</h3>
			<button
				type="button"
				onclick={onClose}
				aria-label="Close modal"
				class="ml-auto rounded-lg p-1.5 text-zinc-400 hover:bg-zinc-800 hover:text-white focus:ring-2 focus:ring-zinc-600 focus:outline-none"
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

		<!-- Form for data fetching (hidden) -->
		<form
			method="POST"
			action="?/getUserDetails"
			use:enhance={handleEnhance}
			use:autoSubmit
			class="hidden"
		>
			<input type="hidden" name="userId" value={userId} />
		</form>

		<!-- Modal Body -->
		<div class="p-6">
			{#if loading}
				<div class="flex justify-center py-8" aria-live="polite" aria-busy="true">
					<div
						class="h-8 w-8 animate-spin rounded-full border-4 border-zinc-600 border-t-purple-500"
					></div>
					<span class="sr-only">Loading...</span>
				</div>
			{:else if error}
				<div role="alert" class="rounded-md bg-red-900/20 p-4 text-center text-red-400">
					{error}
				</div>
			{:else if userData}
				<!-- User Info Section -->
				<div class="mb-6">
					<h4 class="mb-3 text-lg font-semibold text-white">User Information</h4>
					<div class="grid grid-cols-1 gap-4 md:grid-cols-2">
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">Username</p>
							<p class="text-white">{userData.username || 'N/A'}</p>
						</div>
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">Email</p>
							<p class="text-white">{userData.email || 'N/A'}</p>
						</div>
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">User ID</p>
							<p class="text-white">{userData.id || 'N/A'}</p>
						</div>
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">Role</p>
							<p>
								<span class={`rounded-full px-2.5 py-0.5 text-xs font-medium ${roleClass}`}>
									{roleLabel}
								</span>
							</p>
						</div>
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">Created At</p>
							<p class="text-white">{formatDate(userData.createdAt)}</p>
						</div>
						<div class="rounded-md bg-zinc-800/50 p-3">
							<p class="text-xs text-zinc-500">Updated At</p>
							<p class="text-white">{formatDate(userData.updatedAt)}</p>
						</div>
					</div>
				</div>

				<!-- User Login History Section -->
				<div>
					<h4 class="mb-3 text-lg font-semibold text-white">Login History</h4>
					{#if !loginHistory.length}
						<p class="rounded-md bg-zinc-800/50 p-4 text-center text-zinc-400">
							No login history available
						</p>
					{:else}
						<div class="max-h-64 overflow-y-auto rounded-lg border border-zinc-800">
							<table class="w-full table-auto">
								<thead>
									<tr class="border-b border-zinc-800 text-left">
										<th scope="col" class="px-4 py-2 text-sm font-medium text-zinc-400">Date</th>
										<th scope="col" class="px-4 py-2 text-sm font-medium text-zinc-400"
											>IP Address</th
										>
										<th scope="col" class="px-4 py-2 text-sm font-medium text-zinc-400"
											>User Agent</th
										>
										<th scope="col" class="px-4 py-2 text-sm font-medium text-zinc-400">Status</th>
									</tr>
								</thead>
								<tbody>
									{#each loginHistory as login (login.id)}
										<tr class="border-b border-zinc-800">
											<td class="px-4 py-2 text-sm text-zinc-300">
												{formatDate(login.createdAt)}
											</td>
											<td class="px-4 py-2 text-sm text-zinc-300">{login.ipAddress || 'Unknown'}</td
											>
											<td class="max-w-[200px] truncate px-4 py-2 text-sm text-zinc-300">
												<span title={login.userAgent || undefined}>
													{login.userAgent || 'Unknown'}
												</span>
											</td>
											<td class="px-4 py-2">
												<span
													class={`inline-block rounded px-2 py-1 text-xs ${
														login.success
															? 'bg-green-900/20 text-green-400'
															: 'bg-red-900/20 text-red-400'
													}`}
												>
													{login.success ? 'Success' : 'Failed'}
												</span>
											</td>
										</tr>
									{/each}
								</tbody>
							</table>
						</div>
					{/if}
				</div>
			{:else}
				<div class="rounded-md bg-zinc-800/50 p-4 text-center text-zinc-400">
					No user data available
				</div>
			{/if}
		</div>

		<!-- Modal Footer -->
		<div class="flex justify-end border-t border-zinc-800 p-4">
			<button
				type="button"
				onclick={onClose}
				class="rounded-lg bg-zinc-800 px-4 py-2 text-sm font-medium text-white hover:bg-zinc-700 focus:ring-2 focus:ring-zinc-600 focus:outline-none"
			>
				Close
			</button>
		</div>
	</div>
</div>
