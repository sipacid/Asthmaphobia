<script lang="ts">
	import { enhance } from '$app/forms';
	import { goto } from '$app/navigation';
	import type { PageData } from './$types';
	
	let { data } = $props<{data: PageData}>();
	
	// Form state management
	let showForm = $state(!!data.editUser);
	let formMode = $state<'create' | 'edit'>(data.editUser ? 'edit' : 'create');
	
	// Form data
	let username = $state(data.editUser?.username || '');
	let email = $state(data.editUser?.email || '');
	let role = $state<'user' | 'admin'>(data.editUser?.role || 'user');
	let password = $state('');
	let confirmPassword = $state('');
	
	// Update form when data changes
	$effect(() => {
		if (data.editUser) {
			showForm = true;
			formMode = 'edit';
			username = data.editUser.username || '';
			email = data.editUser.email || '';
			role = data.editUser.role || 'user';
			// Don't set password for edit mode (will be optional)
			password = '';
			confirmPassword = '';
		} else if (formMode === 'edit') {
			showForm = false;
		}
	});
	
	function toggleForm(mode: 'create' | 'edit') {
		if (formMode === mode && showForm) {
			showForm = false;
		} else {
			formMode = mode;
			showForm = true;
			
			if (mode === 'create') {
				username = '';
				email = '';
				role = 'user';
				password = '';
				confirmPassword = '';
			}
		}
	}
	
	function handleSubmit() {
		return async ({ update, result }: any) => {
			if (result.data?.success) {
				showForm = false;
				await goto('/admin/users', { replaceState: true });
				await update();
			}
		};
	}
	
	function confirmDelete() {
		return confirm('Are you sure you want to delete this user?');
	}
	
	function handleFormDelete(event: Event, shouldDelete: boolean) {
		event.preventDefault();
		if (shouldDelete) {
			(event.target as HTMLButtonElement).form?.submit();
		}
	}
	
	function formatDate(date: string | Date): string {
		return new Date(date).toLocaleDateString();
	}
	
	// Form validation
	let passwordsMatch = $derived(
		formMode === 'edit' ? 
			(password === '' || password === confirmPassword) : 
			password === confirmPassword
	);
</script>

<div class="container mx-auto max-w-6xl px-4 py-8">
	<!-- Page Header -->
	<div class="mb-8 flex items-center justify-between">
		<div>
			<h1 class="text-2xl font-bold text-white">User Management</h1>
			<p class="text-zinc-400">Create, edit, and manage user accounts</p>
		</div>
		<div class="flex space-x-2">
			<a href="/admin" class="rounded-lg bg-zinc-800 px-3 py-2 text-sm text-zinc-300 hover:bg-zinc-700">
				Back to Admin
			</a>
			<button 
				onclick={() => toggleForm('create')}
				class="rounded-lg bg-purple-600 px-3 py-2 text-sm text-white hover:bg-purple-700"
			>
				New User
			</button>
		</div>
	</div>

	<!-- User Form (Create or Edit) -->
	{#if showForm}
		<div class="mb-8 rounded-lg border border-zinc-800 bg-zinc-900/70 p-6">
			<h2 class="mb-4 text-lg font-semibold text-white">
				{formMode === 'create' ? 'Create New User' : 'Edit User'}
			</h2>
			
			<form method="POST" action="?/{formMode}" use:enhance={handleSubmit}>
				{#if formMode === 'edit' && data.editUser}
					<input type="hidden" name="id" value={data.editUser.id} />
				{/if}
				
				<div class="mb-4 grid grid-cols-2 gap-4">
					<div>
						<label for="username" class="mb-1 block text-sm font-medium text-zinc-300">Username</label>
						<input 
							type="text" 
							id="username" 
							name="username"
							bind:value={username}
							class="w-full rounded-md border border-zinc-700 bg-zinc-800 px-3 py-2 text-white focus:border-purple-500 focus:outline-none"
							required
						/>
					</div>
					
					<div>
						<label for="email" class="mb-1 block text-sm font-medium text-zinc-300">Email</label>
						<input 
							type="email" 
							id="email" 
							name="email"
							bind:value={email}
							class="w-full rounded-md border border-zinc-700 bg-zinc-800 px-3 py-2 text-white focus:border-purple-500 focus:outline-none"
							required
						/>
					</div>
				</div>
				
				<div class="mb-4 grid grid-cols-2 gap-4">
					<div>
						<label for="password" class="mb-1 block text-sm font-medium text-zinc-300">
							{formMode === 'edit' ? 'Password (leave blank to keep current)' : 'Password'}
						</label>
						<input 
							type="password" 
							id="password" 
							name="password"
							bind:value={password}
							class="w-full rounded-md border border-zinc-700 bg-zinc-800 px-3 py-2 text-white focus:border-purple-500 focus:outline-none"
							required={formMode === 'create'}
						/>
					</div>
					
					<div>
						<label for="confirmPassword" class="mb-1 block text-sm font-medium text-zinc-300">Confirm Password</label>
						<input 
							type="password" 
							id="confirmPassword" 
							name="confirmPassword"
							bind:value={confirmPassword}
							class="w-full rounded-md border border-zinc-700 bg-zinc-800 px-3 py-2 text-white focus:border-purple-500 focus:outline-none"
							required={formMode === 'create'}
						/>
						{#if !passwordsMatch}
							<p class="mt-1 text-xs text-red-400">Passwords don't match</p>
						{/if}
					</div>
				</div>
				
				<div class="mb-4">
					<label for="role" class="mb-1 block text-sm font-medium text-zinc-300">Role</label>
					<div class="flex items-center space-x-4 rounded-md border border-zinc-700 bg-zinc-800 p-2">
						<label class="flex items-center space-x-2">
							<input 
								type="radio" 
								name="role" 
								value="user" 
								checked={role === 'user'}
								onchange={() => role = 'user'}
								class="text-purple-600 focus:ring-purple-500"
							/>
							<span class="text-sm text-white">Standard User</span>
						</label>
						
						<label class="flex items-center space-x-2">
							<input 
								type="radio" 
								name="role" 
								value="admin" 
								checked={role === 'admin'}
								onchange={() => role = 'admin'}
								class="text-purple-600 focus:ring-purple-500"
							/>
							<span class="text-sm text-white">Administrator</span>
						</label>
					</div>
				</div>
				
				<div class="flex justify-end space-x-2">
					{#if formMode === 'edit'}
						<a 
							href="/admin/users"
							class="rounded-lg border border-zinc-700 bg-zinc-800 px-4 py-2 text-sm text-zinc-300 hover:bg-zinc-700"
						>
							Cancel
						</a>
					{:else}
						<button 
							type="button"
							onclick={() => showForm = false}
							class="rounded-lg border border-zinc-700 bg-zinc-800 px-4 py-2 text-sm text-zinc-300 hover:bg-zinc-700"
						>
							Cancel
						</button>
					{/if}
					<button 
						type="submit"
						class="rounded-lg bg-purple-600 px-4 py-2 text-sm text-white hover:bg-purple-700"
						disabled={!passwordsMatch}
					>
						{formMode === 'create' ? 'Create User' : 'Update User'}
					</button>
				</div>
			</form>
		</div>
	{/if}
	
	<!-- Users Table -->
	<div class="rounded-lg border border-zinc-800 bg-zinc-900/70">
		<div class="p-4">
			<h2 class="text-lg font-semibold text-white">All Users</h2>
		</div>
		
		<div class="overflow-x-auto">
			<table class="w-full table-auto">
				<thead>
					<tr class="border-b border-zinc-800 text-left">
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Username</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Email</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Role</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Created</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Actions</th>
					</tr>
				</thead>
				<tbody>
					{#if data.users?.length === 0}
						<tr class="border-b border-zinc-800">
							<td colspan="5" class="px-4 py-4 text-center text-zinc-500">No users found.</td>
						</tr>
					{:else}
						{#each data.users as user (user.id)}
							<tr class="border-b border-zinc-800">
								<td class="px-4 py-3 text-sm text-white">
									{user.username}
									{#if user.id === data.currentUser?.id}
										<span class="ml-1 text-xs text-zinc-500">(you)</span>
									{/if}
								</td>
								<td class="px-4 py-3 text-sm text-zinc-400">
									{user.email}
								</td>
								<td class="px-4 py-3">
									<span class={`rounded-full px-2.5 py-0.5 text-xs font-medium ${user.role === 'admin' ? 'bg-purple-900/20 text-purple-400' : 'bg-blue-900/20 text-blue-400'}`}>
										{user.role === 'admin' ? 'Administrator' : 'User'}
									</span>
								</td>
								<td class="px-4 py-3 text-sm text-zinc-400">
									{formatDate(user.created_at)}
								</td>
								<td class="px-4 py-3">
									<div class="flex items-center space-x-2">
										<a 
											href={`/admin/users?edit=${user.id}`}
											class="rounded px-2 py-1 text-xs font-medium text-purple-400 hover:bg-zinc-800"
										>
											Edit
										</a>
										
										{#if user.id !== data.currentUser?.id}
											<form action="?/delete" method="POST" use:enhance={handleSubmit} class="inline-block">
												<input type="hidden" name="id" value={user.id} />
												<button 
													type="submit"
													class="rounded px-2 py-1 text-xs font-medium text-red-400 hover:bg-zinc-800 cursor-pointer"
													onclick={(e) => handleFormDelete(e, confirmDelete())}
												>
													Delete
												</button>
											</form>
										{/if}
									</div>
								</td>
							</tr>
						{/each}
					{/if}
				</tbody>
			</table>
		</div>
	</div>
</div>
