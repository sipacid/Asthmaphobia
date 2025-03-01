<script lang="ts">
	import { enhance } from '$app/forms';
	import type { ActionData } from './$types';

	let { form }: { form: ActionData } = $props();
	let showPassword = $state(false);
</script>

<div class="flex min-h-svh w-full items-center justify-center bg-black px-4 py-12">
	<div class="w-full max-w-md">
		<div class="mx-auto mb-8 flex justify-center">
			<!-- Logo placeholder - replace with actual logo if available -->
			<div class="flex h-12 w-12 items-center justify-center rounded-full bg-purple-700">
				<svg xmlns="http://www.w3.org/2000/svg" class="h-7 w-7 text-white" fill="none" viewBox="0 0 24 24" stroke="currentColor">
					<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M17 20h5v-2a3 3 0 00-5.356-1.857M17 20H7m10 0v-2c0-.656-.126-1.283-.356-1.857M7 20H2v-2a3 3 0 015.356-1.857M7 20v-2c0-.656.126-1.283.356-1.857m0 0a5.002 5.002 0 019.288 0M15 7a3 3 0 11-6 0 3 3 0 016 0zm6 3a2 2 0 11-4 0 2 2 0 014 0zM7 10a2 2 0 11-4 0 2 2 0 014 0z" />
				</svg>
			</div>
		</div>
		
		<div class="rounded-xl border border-zinc-800 bg-zinc-900 p-8 shadow-xl">
			<h1 class="mb-6 text-center text-2xl font-bold text-white">Sign In</h1>
			
			{#if form?.message}
				<div class="mb-6 rounded border-l-4 border-red-600 bg-red-900/20 p-3 text-red-400">
					<p>{form.message}</p>
				</div>
			{/if}
			
			<form method="POST" action="?/login" use:enhance class="space-y-5">
				<div>
					<label for="email" class="mb-1 block text-sm font-medium text-zinc-300">
						Email address
					</label>
					<div class="relative">
						<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
							<svg xmlns="http://www.w3.org/2000/svg" class="h-5 w-5 text-zinc-600" fill="none" viewBox="0 0 24 24" stroke="currentColor">
								<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M3 8l7.89 5.26a2 2 0 002.22 0L21 8M5 19h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v10a2 2 0 002 2z" />
							</svg>
						</div>
						<input 
							name="email" 
							id="email" 
							type="email"
							class="w-full rounded-lg border border-zinc-800 bg-black py-3 pl-10 pr-3 text-zinc-200 focus:border-purple-600 focus:outline-none focus:ring-1 focus:ring-purple-600"
							placeholder="your@email.com"
							required
						/>
					</div>
				</div>
				
				<div>
					<label for="password" class="mb-1 block text-sm font-medium text-zinc-300">
						Password
					</label>
					<div class="relative">
						<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
							<svg xmlns="http://www.w3.org/2000/svg" class="h-5 w-5 text-zinc-600" fill="none" viewBox="0 0 24 24" stroke="currentColor">
								<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 15v2m-6 4h12a2 2 0 002-2v-6a2 2 0 00-2-2H6a2 2 0 00-2 2v6a2 2 0 002 2zm10-10V7a4 4 0 00-8 0v4h8z" />
							</svg>
						</div>
						<input 
							name="password" 
							id="password" 
							type={showPassword ? 'text' : 'password'}
							class="w-full rounded-lg border border-zinc-800 bg-black py-3 pl-10 pr-10 text-zinc-200 focus:border-purple-600 focus:outline-none focus:ring-1 focus:ring-purple-600"
							placeholder="••••••••"
							required
						/>
						<button 
							type="button"
							class="absolute inset-y-0 right-0 flex items-center pr-3 text-zinc-500 hover:text-zinc-300"
							onclick={() => showPassword = !showPassword}
						>
							{#if showPassword}
								<svg xmlns="http://www.w3.org/2000/svg" class="h-5 w-5" fill="none" viewBox="0 0 24 24" stroke="currentColor">
									<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13.875 18.825A10.05 10.05 0 0112 19c-4.478 0-8.268-2.943-9.543-7a9.97 9.97 0 011.563-3.029m5.858.908a3 3 0 114.243 4.243M9.878 9.878l4.242 4.242M9.88 9.88l-3.29-3.29m7.532 7.532l3.29 3.29M3 3l3.59 3.59m0 0A9.953 9.953 0 0112 5c4.478 0 8.268 2.943 9.543 7a10.025 10.025 0 01-4.132 5.411m0 0L21 21" />
								</svg>
							{:else}
								<svg xmlns="http://www.w3.org/2000/svg" class="h-5 w-5" fill="none" viewBox="0 0 24 24" stroke="currentColor">
									<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z" />
									<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z" />
								</svg>
							{/if}
						</button>
					</div>
				</div>
				
				<div class="pt-2">
					<button
						type="submit"
						class="w-full rounded-lg bg-purple-700 px-5 py-3 text-center text-sm font-semibold text-white shadow-md transition-colors hover:bg-purple-600 focus:outline-none focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black"
					>
						Sign in
					</button>
				</div>
			</form>
			
			<div class="mt-6 text-center">
				<p class="text-sm text-zinc-500">
					Don't have an account yet? 
					<a href="/auth/register" class="font-medium text-purple-500 hover:text-purple-400">
						Sign up
					</a>
				</p>
			</div>
		</div>
	</div>
</div>
