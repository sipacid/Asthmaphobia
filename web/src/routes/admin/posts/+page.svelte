<script lang="ts">
	import { enhance } from '$app/forms';
	import { goto } from '$app/navigation';
	import type { PageData } from './$types';
	
	let { data } = $props<{data: PageData}>();
	
	// Form state management
	let showForm = $state(!!data.editPost);
	let formMode = $state<'create' | 'edit'>(data.editPost ? 'edit' : 'create');
	
	// Form data
	let title = $state(data.editPost?.title || '');
	let content = $state(data.editPost?.content || '');
	let type = $state<'news' | 'release'>(data.editPost?.type || 'news');
	let published = $state(data.editPost?.published || false);
	
	// Update form when data changes
	$effect(() => {
		if (data.editPost) {
			showForm = true;
			formMode = 'edit';
			title = data.editPost.title || '';
			content = data.editPost.content || '';
			type = data.editPost.type || 'news';
			published = data.editPost.published || false;
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
				title = '';
				content = '';
				type = 'news';
				published = false;
			}
		}
	}
	
	function handleSubmit() {
		return async ({ update, result }: any) => {
			console.log(result);
			if (result.data.success) {
				showForm = false;
				await goto('/admin/posts', { replaceState: true });
				await update();
			}
		};
	}
	
	function confirmDelete() {
		return confirm('Are you sure you want to delete this post?');
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
			<h1 class="text-2xl font-bold text-white">Posts Management</h1>
			<p class="text-zinc-400">Create and edit news posts and software release announcements</p>
		</div>
		<div class="flex space-x-2">
			<a href="/admin" class="rounded-lg bg-zinc-800 px-3 py-2 text-sm text-zinc-300 hover:bg-zinc-700">
				Back to Admin
			</a>
			<button 
				onclick={() => toggleForm('create')}
				class="rounded-lg bg-purple-600 px-3 py-2 text-sm text-white hover:bg-purple-700"
			>
				New Post
			</button>
		</div>
	</div>

	<!-- Post Form (Create or Edit) -->
	{#if showForm}
		<div class="mb-8 rounded-lg border border-zinc-800 bg-zinc-900/70 p-6">
			<h2 class="mb-4 text-lg font-semibold text-white">
				{formMode === 'create' ? 'Create New Post' : 'Edit Post'}
			</h2>
			
			<form method="POST" action="?/{formMode}" use:enhance={handleSubmit}>
				{#if formMode === 'edit' && data.editPost}
					<input type="hidden" name="id" value={data.editPost.id} />
				{/if}
				
				<div class="mb-4">
					<label for="title" class="mb-1 block text-sm font-medium text-zinc-300">Title</label>
					<input 
						type="text" 
						id="title" 
						name="title"
						bind:value={title}
						class="w-full rounded-md border border-zinc-700 bg-zinc-800 px-3 py-2 text-white focus:border-purple-500 focus:outline-none"
						required
					/>
				</div>
				
				<div class="mb-4">
					<label for="content" class="mb-1 block text-sm font-medium text-zinc-300">Content (Markdown)</label>
					<textarea 
						id="content" 
						name="content"
						bind:value={content}
						class="h-64 w-full rounded-md border border-zinc-700 bg-zinc-800 px-3 py-2 text-white focus:border-purple-500 focus:outline-none"
						required
					></textarea>
				</div>
				
				<div class="mb-4 grid grid-cols-2 gap-4">
					<div>
						<label for="type" class="mb-1 block text-sm font-medium text-zinc-300">Type</label>
						<select 
							id="type" 
							name="type"
							bind:value={type}
							class="w-full rounded-md border border-zinc-700 bg-zinc-800 px-3 py-2 text-white focus:border-purple-500 focus:outline-none"
						>
							<option value="news">News Post</option>
							<option value="release">Release Notes</option>
						</select>
					</div>
					
					<div>
						<label for="published" class="mb-1 block text-sm font-medium text-zinc-300">Status</label>
						<div class="flex items-center space-x-4 rounded-md border border-zinc-700 bg-zinc-800 p-2">
							<label class="flex items-center space-x-2">
								<input 
									type="radio" 
									name="published" 
									value="true" 
									checked={published}
									onchange={() => published = true}
									class="text-purple-600 focus:ring-purple-500"
								/>
								<span class="text-sm text-white">Published</span>
							</label>
							
							<label class="flex items-center space-x-2">
								<input 
									type="radio" 
									name="published" 
									value="false" 
									checked={!published}
									onchange={() => published = false}
									class="text-purple-600 focus:ring-purple-500"
								/>
								<span class="text-sm text-white">Draft</span>
							</label>
						</div>
					</div>
				</div>
				
				<div class="flex justify-end space-x-2">
					{#if formMode === 'edit'}
						<a 
							href="/admin/posts"
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
					>
						{formMode === 'create' ? 'Create Post' : 'Update Post'}
					</button>
				</div>
			</form>
		</div>
	{/if}
	
	<!-- Posts Table -->
	<div class="rounded-lg border border-zinc-800 bg-zinc-900/70">
		<div class="p-4">
			<h2 class="text-lg font-semibold text-white">All Posts</h2>
		</div>
		
		<div class="overflow-x-auto">
			<table class="w-full table-auto">
				<thead>
					<tr class="border-b border-zinc-800 text-left">
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Title</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Type</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Author</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Date</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Status</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Actions</th>
					</tr>
				</thead>
				<tbody>
					{#if data.posts?.length === 0}
						<tr class="border-b border-zinc-800">
							<td colspan="6" class="px-4 py-4 text-center text-zinc-500">No posts found.</td>
						</tr>
					{:else}
						{#each data.posts as post (post.id)}
							<tr class="border-b border-zinc-800">
								<td class="px-4 py-3 text-sm text-white">
									{post.title}
								</td>
								<td class="px-4 py-3 text-sm text-zinc-400">
									{post.type === 'news' ? 'News Post' : 'Release Notes'}
								</td>
								<td class="px-4 py-3 text-sm text-zinc-400">
									{post.author_name}
								</td>
								<td class="px-4 py-3 text-sm text-zinc-400">
									{new Date(post.created_at).toLocaleDateString()}
								</td>
								<td class="px-4 py-3">
									<span class={`rounded-full px-2.5 py-0.5 text-xs font-medium ${post.published ? 'bg-green-900/20 text-green-400' : 'bg-amber-900/20 text-amber-400'}`}>
										{post.published ? 'Published' : 'Draft'}
									</span>
								</td>
								<td class="px-4 py-3">
									<div class="flex items-center space-x-2">
										<a 
											href={`/admin/posts?edit=${post.id}`}
											class="rounded px-2 py-1 text-xs font-medium text-purple-400 hover:bg-zinc-800"
										>
											Edit
										</a>
										
										<form action="?/delete" method="POST" use:enhance={handleSubmit} class="inline-block">
											<input type="hidden" name="id" value={post.id} />
											<button 
												type="submit"
												class="rounded px-2 py-1 text-xs font-medium text-red-400 hover:bg-zinc-800 cursor-pointer"
												onclick={(e) => handleFormDelete(e, confirmDelete())}
											>
												Delete
											</button>
										</form>
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
