<script lang="ts">
	import { enhance } from '$app/forms';
	import { goto } from '$app/navigation';
	import type { PageData } from './$types';
	
	let { data } = $props<{data: PageData}>();
	
	// Form state management
	let showForm = $state(!!data.editUser);
	
	// Form data
	let username = $state(data.editUser?.username || '');
	let email = $state(data.editUser?.email || '');
	let role = $state<'user' | 'administrator'>(data.editUser?.role || 'user');
	
	// Update form when data changes
	$effect(() => {
		if (data.editUser) {
			showForm = true;
			username = data.editUser.username || '';
			email = data.editUser.email || '';
			role = data.editUser.role || 'user';
		} else {
			showForm = false;
		}
	});
	
	function handleSubmit() {
		return async ({ update, result }: any) => {
			if (result.data.success) {
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
</script>

<div class="container mx-auto max-w-6xl px-4 py-8">
	<!-- Page Header -->
	<div class="mb-8 flex items-center justify-between">
		<div>
			<h1 class="text-2xl font-bold text-white">User Management</h1>
			<p class="text-zinc-400">Edit, and manage user accounts</p>
		</div>
		<div class="flex space-x-2">
			<a href="/admin" class="rounded-lg bg-zinc-800 px-3 py-2 text-sm text-zinc-300 hover:bg-zinc-700">
				Back to Admin
			</a>
		</div>
	</div>

	<!-- User Form (Edit) -->
	{#if showForm}
		<div class="mb-8 rounded-lg border border-zinc-800 bg-zinc-900/70 p-6">
			<h2 class="mb-4 text-lg font-semibold text-white">
				Edit User
			</h2>
			
			<form method="POST" action="?/edit" use:enhance={handleSubmit}>
				{#if data.editUser}
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
								value="administrator" 
								checked={role === 'administrator'}
								onchange={() => role = 'administrator'}
								class="text-purple-600 focus:ring-purple-500"
							/>
							<span class="text-sm text-white">Administrator</span>
						</label>
					</div>
				</div>
				
				<div class="flex justify-end space-x-2">
					<a 
						href="/admin/users"
						class="rounded-lg border border-zinc-700 bg-zinc-800 px-4 py-2 text-sm text-zinc-300 hover:bg-zinc-700"
					>
						Cancel
					</a>
					<button 
						type="submit"
						class="rounded-lg bg-purple-600 px-4 py-2 text-sm text-white hover:bg-purple-700"
					>
						Update User
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
									<span class={`rounded-full px-2.5 py-0.5 text-xs font-medium ${user.role === 'administrator' ? 'bg-purple-900/20 text-purple-400' : 'bg-blue-900/20 text-blue-400'}`}>
										{user.role === 'administrator' ? 'Administrator' : 'User'}
									</span>
								</td>
								<td class="px-4 py-3 text-sm text-zinc-400">
										{new Date(user.createdAt).toLocaleDateString()}
								</td>
								<td class="px-4 py-3">
									<div class="flex items-center space-x-2">
										<a 
											href={`/admin/users?edit=${user.id}`}
											class="rounded px-2 py-1 text-xs font-medium text-purple-400 hover:bg-zinc-800"
										>
											Edit
										</a>
										
										{#if user.id !== data.user.id}
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
