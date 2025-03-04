<script lang="ts">
	import { enhance } from '$app/forms';
	import { getReCaptchaToken } from '$lib/utils/recaptcha';
	import type { ActionData } from './$types';

	let { form }: { form: ActionData } = $props();
	let showPassword = $state(false);
	let showConfirmPassword = $state(false);
	let isSubmitting = $state(false);

	async function handleSubmit(input: {
		action: URL;
		formData: FormData;
		formElement: HTMLFormElement;
		controller: AbortController;
		submitter: HTMLElement | null;
		cancel: () => void;
	}) {
		isSubmitting = true;
		const token = await getReCaptchaToken('register');
		input.formData.append('recaptcha_token', token);

		return async ({ update }) => {
			isSubmitting = false;
			await update();
		};
	}
</script>

<div class="flex min-h-svh w-full items-center justify-center bg-black px-4 py-12">
	<div class="w-full max-w-md">
		<div class="mx-auto mb-8 flex justify-center">
			<!-- Logo placeholder - replace with actual logo if available -->
			<div class="flex h-12 w-12 items-center justify-center rounded-full bg-purple-700">
				<svg
					xmlns="http://www.w3.org/2000/svg"
					class="h-7 w-7 text-white"
					fill="none"
					viewBox="0 0 24 24"
					stroke="currentColor"
				>
					<path
						stroke-linecap="round"
						stroke-linejoin="round"
						stroke-width="2"
						d="M18 9v3m0 0v3m0-3h3m-3 0h-3m-2-5a4 4 0 11-8 0 4 4 0 018 0zM3 20a6 6 0 0112 0v1H3v-1z"
					/>
				</svg>
			</div>
		</div>

		<div class="rounded-xl border border-zinc-800 bg-zinc-900 p-8 shadow-xl">
			<h1 class="mb-6 text-center text-2xl font-bold text-white">Create an Account</h1>

			{#if form?.message}
				<div class="mb-6 rounded border-l-4 border-red-600 bg-red-900/20 p-3 text-red-400">
					<p>{form.message}</p>
				</div>
			{/if}

			<form method="POST" action="?/register" use:enhance={handleSubmit} class="space-y-5">
				<div>
					<label for="email" class="mb-1 block text-sm font-medium text-zinc-300">
						Email address <span class="text-purple-500">*</span>
					</label>
					<div class="relative">
						<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="h-5 w-5 text-zinc-600"
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
							class="w-full rounded-lg border border-zinc-800 bg-black py-3 pr-3 pl-10 text-zinc-200 focus:border-purple-600 focus:ring-1 focus:ring-purple-600 focus:outline-none"
							placeholder="your@email.com"
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
								class="h-5 w-5 text-zinc-600"
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
							class="w-full rounded-lg border border-zinc-800 bg-black py-3 pr-3 pl-10 text-zinc-200 focus:border-purple-600 focus:ring-1 focus:ring-purple-600 focus:outline-none"
							placeholder="johndoe"
							required
						/>
					</div>
				</div>

				<div>
					<label for="password" class="mb-1 block text-sm font-medium text-zinc-300">
						Password <span class="text-purple-500">*</span>
					</label>
					<div class="relative">
						<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="h-5 w-5 text-zinc-600"
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
							class="w-full rounded-lg border border-zinc-800 bg-black py-3 pr-10 pl-10 text-zinc-200 focus:border-purple-600 focus:ring-1 focus:ring-purple-600 focus:outline-none"
							placeholder="••••••••"
							required
						/>
						<button
							type="button"
							class="absolute inset-y-0 right-0 flex items-center pr-3 text-zinc-500 hover:text-zinc-300"
							onclick={() => (showPassword = !showPassword)}
						>
							{#if showPassword}
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="h-5 w-5"
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
									class="h-5 w-5"
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
					<p class="mt-1 text-xs text-zinc-600">
						Use at least 8 characters with a mix of letters and numbers
					</p>
				</div>

				<div>
					<label for="confirm-password" class="mb-1 block text-sm font-medium text-zinc-300">
						Confirm Password <span class="text-purple-500">*</span>
					</label>
					<div class="relative">
						<div class="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-3">
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="h-5 w-5 text-zinc-600"
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
							class="w-full rounded-lg border border-zinc-800 bg-black py-3 pr-10 pl-10 text-zinc-200 focus:border-purple-600 focus:ring-1 focus:ring-purple-600 focus:outline-none"
							placeholder="••••••••"
							required
						/>
						<button
							type="button"
							class="absolute inset-y-0 right-0 flex items-center pr-3 text-zinc-500 hover:text-zinc-300"
							onclick={() => (showConfirmPassword = !showConfirmPassword)}
						>
							{#if showConfirmPassword}
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="h-5 w-5"
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
									class="h-5 w-5"
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

				<div class="pt-2">
					<button
						type="submit"
						class="w-full rounded-lg bg-purple-700 px-5 py-3 text-center text-sm font-semibold text-white shadow-md transition-colors hover:bg-purple-600 focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black focus:outline-none disabled:opacity-70"
						disabled={isSubmitting}
					>
						{#if isSubmitting}
							<span class="inline-flex items-center">
								<svg
									class="mr-2 h-4 w-4 animate-spin"
									xmlns="http://www.w3.org/2000/svg"
									fill="none"
									viewBox="0 0 24 24"
								>
									<circle
										class="opacity-25"
										cx="12"
										cy="12"
										r="10"
										stroke="currentColor"
										stroke-width="4"
									></circle>
									<path
										class="opacity-75"
										fill="currentColor"
										d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"
									></path>
								</svg>
								Creating account...
							</span>
						{:else}
							Create Account
						{/if}
					</button>
				</div>

				<p class="text-center text-xs text-zinc-500">
					This site is protected by reCAPTCHA and the Google
					<a
						href="https://policies.google.com/privacy"
						class="text-purple-500 hover:text-purple-400">Privacy Policy</a
					>
					and
					<a href="https://policies.google.com/terms" class="text-purple-500 hover:text-purple-400"
						>Terms of Service</a
					> apply.
				</p>
			</form>

			<div class="mt-6 text-center">
				<p class="text-sm text-zinc-500">
					Already have an account?
					<a href="/auth/login" class="font-medium text-purple-500 hover:text-purple-400">
						Sign in
					</a>
				</p>
			</div>
		</div>
	</div>
</div>
