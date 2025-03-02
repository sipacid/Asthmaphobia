<script lang="ts">
	import { onMount } from 'svelte';

	// Accept user data as a prop
	let { user } = $props<{ user?: any | null }>();

	// Local state for dropdown menu
	let isProfileMenuOpen = $state(false);

	// Function to toggle dropdown menu
	const toggleProfileMenu = () => {
		isProfileMenuOpen = !isProfileMenuOpen;
	};

	// Close dropdown when clicking outside
	const handleClickOutside = (event: MouseEvent) => {
		const dropdown = document.getElementById('profile-dropdown');
		if (dropdown && !dropdown.contains(event.target as Node) && isProfileMenuOpen) {
			isProfileMenuOpen = false;
		}
	};

	// Setup click listener
	onMount(() => {
		document.addEventListener('click', handleClickOutside);
		return () => document.removeEventListener('click', handleClickOutside);
	});
</script>

<header class="fixed top-0 right-0 left-0 z-50 h-14 w-full bg-zinc-950 px-4 text-white shadow-md">
	<div class="container mx-auto flex h-full items-center justify-between">
		<div class="text-lg font-bold">
			<a href="/" class="flex items-center">
				<span class="text-purple-500">Asthma</span>phobia
			</a>
		</div>
		<nav>
			<ul class="flex items-center space-x-4">
				<li>
					<a href="/" class="text-sm font-medium transition duration-200 hover:text-purple-400"
						>Home</a
					>
				</li>
				<li>
					<a
						href="/dashboard"
						class="text-sm font-medium transition duration-200 hover:text-purple-400"
					>
						Dashboard
					</a>
				</li>

				{#if user}
					<li class="relative" id="profile-dropdown">
						<button
							onclick={toggleProfileMenu}
							class="flex items-center space-x-1 rounded-full bg-zinc-800 px-3 py-1.5 text-sm transition hover:bg-zinc-700"
						>
							<div
								class="flex h-6 w-6 items-center justify-center rounded-full bg-purple-700 text-xs"
							>
								{user.username.charAt(0).toUpperCase()}
							</div>
							<span class="hidden sm:inline">{user.username}</span>
							<svg
								xmlns="http://www.w3.org/2000/svg"
								class="h-4 w-4"
								fill="none"
								viewBox="0 0 24 24"
								stroke="currentColor"
							>
								<path
									stroke-linecap="round"
									stroke-linejoin="round"
									stroke-width="2"
									d="M19 9l-7 7-7-7"
								/>
							</svg>
						</button>

						{#if isProfileMenuOpen}
							<div
								class="absolute right-0 mt-2 w-48 rounded-md border border-zinc-800 bg-zinc-900 py-1 shadow-lg"
							>
								{#if user.role === 'administrator'}
									<a href="/admin" class="block px-4 py-2 text-sm text-zinc-200 hover:bg-zinc-800">
										<div class="flex items-center space-x-2">
											<svg
												xmlns="http://www.w3.org/2000/svg"
												class="h-4 w-4 text-purple-500"
												fill="none"
												viewBox="0 0 24 24"
												stroke="currentColor"
											>
												<path
													stroke-linecap="round"
													stroke-linejoin="round"
													stroke-width="2"
													d="M10.325 4.317c.426-1.756 2.924-1.756 3.35 0a1.724 1.724 0 002.573 1.066c1.543-.94 3.31.826 2.37 2.37a1.724 1.724 0 001.065 2.572c1.756.426 1.756 2.924 0 3.35a1.724 1.724 0 00-1.066 2.573c.94 1.543-.826 3.31-2.37 2.37a1.724 1.724 0 00-2.572 1.065c-.426 1.756-2.924 1.756-3.35 0a1.724 1.724 0 00-2.573-1.066c-1.543.94-3.31-.826-2.37-2.37a1.724 1.724 0 00-1.065-2.572c-1.756-.426-1.756-2.924 0-3.35a1.724 1.724 0 001.066-2.573c-.94-1.543.826-3.31 2.37-2.37.996.608 2.296.07 2.572-1.065z"
												/>
												<path
													stroke-linecap="round"
													stroke-linejoin="round"
													stroke-width="2"
													d="M15 12a3 3 0 11-6 0 3 3 0 016 0z"
												/>
											</svg>
											<span>Admin Panel</span>
										</div>
									</a>
								{/if}
								<a href="/user" class="block px-4 py-2 text-sm text-zinc-200 hover:bg-zinc-800">
									<div class="flex items-center space-x-2">
										<svg
											xmlns="http://www.w3.org/2000/svg"
											class="h-4 w-4 text-purple-500"
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
										<span>My Profile</span>
									</div>
								</a>
								<hr class="my-1 border-zinc-800" />
								<form method="POST" action="/user?/logout">
									<button
										type="submit"
										class="flex w-full items-center px-4 py-2 text-left text-sm text-red-400 hover:bg-zinc-800"
									>
										<svg
											xmlns="http://www.w3.org/2000/svg"
											class="mr-2 h-4 w-4"
											fill="none"
											viewBox="0 0 24 24"
											stroke="currentColor"
										>
											<path
												stroke-linecap="round"
												stroke-linejoin="round"
												stroke-width="2"
												d="M17 16l4-4m0 0l-4-4m4 4H7m6 4v1a3 3 0 01-3 3H6a3 3 0 01-3-3V7a3 3 0 013-3h4a3 3 0 013 3v1"
											/>
										</svg>
										Sign Out
									</button>
								</form>
							</div>
						{/if}
					</li>
				{/if}
			</ul>
		</nav>
	</div>
</header>
