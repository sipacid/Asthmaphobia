<script lang="ts">
	import { page } from '$app/state';
</script>

<div class="min-h-[calc(100vh-3.5rem)] bg-black">
	<div class="container mx-auto max-w-6xl px-4 py-8 flex flex-col items-center justify-center min-h-[70vh]">
		<div class="rounded-xl border border-zinc-800 bg-zinc-900/70 p-6 text-center w-full max-w-md">
			<div class="mb-8 text-center">
				<span class="text-6xl">⚠️</span>
			</div>
			
			<h1 class="mb-2 text-3xl font-bold text-white">Error {page.status}</h1>
			
			<p class="mb-6 text-lg text-zinc-400">
				{page.error?.message || 'Something went wrong'}
			</p>
			
			<div class="mb-8 rounded-lg bg-black/30 p-4">
				{#if page.status === 404}
					<p class="text-zinc-400">The page you're looking for doesn't exist or has been moved.</p>
				{:else if page.status === 403}
					<p class="text-zinc-400">You don't have permission to access this resource.</p>
				{:else if page.status === 500}
					<p class="text-zinc-400">There was a problem with our server. Please try again later.</p>
				{:else}
					<p class="text-zinc-400">An unexpected error occurred. Please try again or contact support if the problem persists.</p>
				{/if}
			</div>

			<a href="/" class="flex w-full items-center justify-center rounded-lg bg-purple-700 py-2.5 px-4 text-sm font-medium text-white transition hover:bg-purple-600 focus:outline-none focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black">
				<svg xmlns="http://www.w3.org/2000/svg" class="mr-2 h-4 w-4" fill="none" viewBox="0 0 24 24" stroke="currentColor">
					<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M10 19l-7-7m0 0l7-7m-7 7h18" />
				</svg>
				Back to Home
			</a>
		</div>
	</div>
</div>
