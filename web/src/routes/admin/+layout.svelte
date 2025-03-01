<script lang="ts">
	import { page } from '$app/stores';
	let { children } = $props();
	
	const isActive = (href: string) => {
		if (href === '/admin') {
			return $page.url.pathname === href;
		}
		return $page.url.pathname.startsWith(href);
	};
</script>

<main class="min-h-[calc(100vh-3.5rem)] bg-black pt-6 text-white">
	<div class="container mx-auto px-4">
		<div class="mb-6 flex justify-between">
			<div class="flex items-center">
				<h1 class="text-lg font-semibold text-white">Admin Portal</h1>
			</div>
			<nav>
				<ul class="flex space-x-6">
						<li>
							<a 
								href="/admin" 
								class={`flex items-center text-sm font-medium transition-colors duration-200 ${isActive("/admin") ? 'text-purple-400' : 'text-zinc-400 hover:text-zinc-200'}`}
							>
								<svg 
									xmlns="http://www.w3.org/2000/svg" 
									class="mr-1.5 h-4 w-4" 
									fill="none" 
									viewBox="0 0 24 24" 
									stroke="currentColor"
									><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 20H5a2 2 0 01-2-2V6a2 2 0 012-2h10a2 2 0 012 2v1m2 13a2 2 0 01-2-2V7m2 13a2 2 0 002-2V9a2 2 0 00-2-2h-2m-4-3H9M7 16h6M7 8h6v4H7V8z" /></svg
								>
								Dashboard
							</a>
						</li>
						<li>
							<a 
								href="/admin/posts" 
								class={`flex items-center text-sm font-medium transition-colors duration-200 ${isActive("/admin/posts") ? 'text-purple-400' : 'text-zinc-400 hover:text-zinc-200'}`}
							>
								<svg 
									xmlns="http://www.w3.org/2000/svg" 
									class="mr-1.5 h-4 w-4" 
									fill="none" 
									viewBox="0 0 24 24" 
									stroke="currentColor"
									><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 20H5a2 2 0 01-2-2V6a2 2 0 012-2h10a2 2 0 012 2v1m2 13a2 2 0 01-2-2V7m2 13a2 2 0 002-2V9a2 2 0 00-2-2h-2m-4-3H9M7 16h6M7 8h6v4H7V8z" /></svg
								>
								Posts
							</a>
						</li>
				</ul>
			</nav>
		</div>
	</div>
	
	{@render children()}
</main>
