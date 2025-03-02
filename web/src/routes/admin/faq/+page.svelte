<script lang="ts">
	import { enhance } from '$app/forms';
	import { goto } from '$app/navigation';
	import type { PageData } from './$types';

	let { data } = $props<{ data: PageData }>();

	// Form state management
	let showForm = $state(!!data.editFaq);
	let formMode = $state<'create' | 'edit'>(data.editFaq ? 'edit' : 'create');

	// Form data
	let question = $state(data.editFaq?.question || '');
	let answer = $state(data.editFaq?.answer || '');
	let ranking = $state(data.editFaq?.ranking || 0);

	// Update form when data changes
	$effect(() => {
		if (data.editFaq) {
			showForm = true;
			formMode = 'edit';
			question = data.editFaq.question || '';
			answer = data.editFaq.answer || '';
			ranking = data.editFaq.ranking || 0;
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
				question = '';
				answer = '';
				ranking = 0;
			}
		}
	}

	function handleSubmit() {
		return async ({ update, result }: any) => {
			if (result.data.success) {
				showForm = false;
				await goto('/admin/faq', { replaceState: true });
				await update();
			}
		};
	}

	function confirmDelete() {
		return confirm('Are you sure you want to delete this FAQ?');
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
			<h1 class="text-2xl font-bold text-white">FAQ Management</h1>
			<p class="text-zinc-400">Create and edit FAQs</p>
		</div>
		<div class="flex space-x-2">
			<a
				href="/admin"
				class="rounded-lg bg-zinc-800 px-3 py-2 text-sm text-zinc-300 hover:bg-zinc-700"
			>
				Back to Admin
			</a>
			<button
				onclick={() => toggleForm('create')}
				class="rounded-lg bg-purple-600 px-3 py-2 text-sm text-white hover:bg-purple-700"
			>
				New FAQ
			</button>
		</div>
	</div>

	<!-- FAQ Form (Create or Edit) -->
	{#if showForm}
		<div class="mb-8 rounded-lg border border-zinc-800 bg-zinc-900/70 p-6">
			<h2 class="mb-4 text-lg font-semibold text-white">
				{formMode === 'create' ? 'Create New FAQ' : 'Edit FAQ'}
			</h2>

			<form method="POST" action="?/{formMode}" use:enhance={handleSubmit}>
				{#if formMode === 'edit' && data.editFaq}
					<input type="hidden" name="id" value={data.editFaq.id} />
				{/if}

				<div class="mb-4">
					<label for="question" class="mb-1 block text-sm font-medium text-zinc-300">Question</label
					>
					<input
						type="text"
						id="question"
						name="question"
						bind:value={question}
						class="w-full rounded-md border border-zinc-700 bg-zinc-800 px-3 py-2 text-white focus:border-purple-500 focus:outline-none"
						required
					/>
				</div>

				<div class="mb-4">
					<label for="answer" class="mb-1 block text-sm font-medium text-zinc-300">Answer</label>
					<input
						type="text"
						id="answer"
						name="answer"
						bind:value={answer}
						class="w-full rounded-md border border-zinc-700 bg-zinc-800 px-3 py-2 text-white focus:border-purple-500 focus:outline-none"
						required
					/>
				</div>

				<div class="mb-4 grid grid-cols-2 gap-4">
					<div>
						<label for="ranking" class="mb-1 block text-sm font-medium text-zinc-300">Ranking</label
						>
						<input
							type="number"
							id="ranking"
							name="ranking"
							bind:value={ranking}
							class="w-full rounded-md border border-zinc-700 bg-zinc-800 px-3 py-2 text-white focus:border-purple-500 focus:outline-none"
						/>
					</div>
				</div>

				<div class="flex justify-end space-x-2">
					{#if formMode === 'edit'}
						<a
							href="/admin/faq"
							class="rounded-lg border border-zinc-700 bg-zinc-800 px-4 py-2 text-sm text-zinc-300 hover:bg-zinc-700"
						>
							Cancel
						</a>
					{:else}
						<button
							type="button"
							onclick={() => (showForm = false)}
							class="rounded-lg border border-zinc-700 bg-zinc-800 px-4 py-2 text-sm text-zinc-300 hover:bg-zinc-700"
						>
							Cancel
						</button>
					{/if}
					<button
						type="submit"
						class="rounded-lg bg-purple-600 px-4 py-2 text-sm text-white hover:bg-purple-700"
					>
						{formMode === 'create' ? 'Create FAQ' : 'Update FAQ'}
					</button>
				</div>
			</form>
		</div>
	{/if}

	<!-- FAQs Table -->
	<div class="rounded-lg border border-zinc-800 bg-zinc-900/70">
		<div class="p-4">
			<h2 class="text-lg font-semibold text-white">All FAQs</h2>
		</div>

		<div class="overflow-x-auto">
			<table class="w-full table-auto">
				<thead>
					<tr class="border-b border-zinc-800 text-left">
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Question</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Answer</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Date</th>
						<th class="px-4 py-2 text-sm font-medium text-zinc-400">Actions</th>
					</tr>
				</thead>
				<tbody>
					{#if data.faqs?.length === 0}
						<tr class="border-b border-zinc-800">
							<td colspan="6" class="px-4 py-4 text-center text-zinc-500">No posts found.</td>
						</tr>
					{:else}
						{#each data.faqs as faq (faq.id)}
							<tr class="border-b border-zinc-800">
								<td class="px-4 py-3 text-sm text-white">
									{faq.question}
								</td>
								<td class="px-4 py-3 text-sm text-white">
									{faq.answer}
								</td>
								<td class="px-4 py-3 text-sm text-zinc-400">
									{new Date(faq.created_at).toLocaleDateString()}
								</td>
								<td class="px-4 py-3">
									<div class="flex items-center space-x-2">
										<a
											href={`/admin/faq?edit=${faq.id}`}
											class="rounded px-2 py-1 text-xs font-medium text-purple-400 hover:bg-zinc-800"
										>
											Edit
										</a>

										<form
											action="?/delete"
											method="POST"
											use:enhance={handleSubmit}
											class="inline-block"
										>
											<input type="hidden" name="id" value={faq.id} />
											<button
												type="submit"
												class="cursor-pointer rounded px-2 py-1 text-xs font-medium text-red-400 hover:bg-zinc-800"
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
