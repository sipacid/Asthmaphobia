<script lang="ts">
	import type { PageData } from './$types';

	let { data }: { data: PageData } = $props();
</script>

<div class="container mx-auto max-w-6xl px-4 py-8">
	<div class="mb-8 flex items-center justify-between">
		<h1 class="text-2xl font-bold text-white">Admin Dashboard</h1>
	</div>

	<div class="mb-8">
		<div class="grid grid-cols-1 gap-4 sm:grid-cols-2 lg:grid-cols-4">
			<div class="rounded-lg border border-zinc-800 bg-zinc-900/70 p-4">
				<h3 class="text-sm font-medium text-zinc-400">Total Downloads</h3>
				<p class="mt-2 text-2xl font-bold text-white">{data.totalDownloads}</p>
			</div>

			<div class="rounded-lg border border-zinc-800 bg-zinc-900/70 p-4">
				<h3 class="text-sm font-medium text-zinc-400">Total Users</h3>
				<p class="mt-2 text-2xl font-bold text-white">{data.totalUsers}</p>
			</div>
		</div>
	</div>

	<h2 class="mb-4 text-lg font-bold text-white">Admin Tools</h2>
	<div class="grid gap-6 md:grid-cols-2 lg:grid-cols-3">
		<a
			href="/admin/posts"
			class="flex h-full flex-col rounded-xl border border-zinc-800 bg-zinc-900/70 p-6 shadow-md transition-colors duration-200 hover:bg-zinc-900"
		>
			<div class="mb-4 flex items-center justify-between">
				<h2 class="text-lg font-bold text-white">Posts Management</h2>
				<svg
					xmlns="http://www.w3.org/2000/svg"
					class="h-5 w-5 text-purple-500"
					fill="none"
					viewBox="0 0 24 24"
					stroke="currentColor"
				>
					<path
						stroke-linecap="round"
						stroke-linejoin="round"
						stroke-width="2"
						d="M19 20H5a2 2 0 01-2-2V6a2 2 0 012-2h10a2 2 0 012 2v1m2 13a2 2 0 01-2-2V7m2 13a2 2 0 002-2V9a2 2 0 00-2-2h-2m-4-3H9M7 16h6M7 8h6v4H7V8z"
					/>
				</svg>
			</div>
			<p class="mb-4 flex-grow text-sm text-zinc-400">
				Create, edit and manage posts and release notes that appear on the dashboard.
			</p>
			<div class="flex justify-end">
				<span class="rounded-full bg-purple-900/20 px-3 py-1 text-xs font-medium text-purple-400"
					>Manage</span
				>
			</div>
		</a>

		<a
			href="/admin/users"
			class="flex h-full flex-col rounded-xl border border-zinc-800 bg-zinc-900/70 p-6 shadow-md transition-colors duration-200 hover:bg-zinc-900"
		>
			<div class="mb-4 flex items-center justify-between">
				<h2 class="text-lg font-bold text-white">User Management</h2>
				<svg
					xmlns="http://www.w3.org/2000/svg"
					class="h-5 w-5 text-purple-500"
					fill="none"
					viewBox="0 0 24 24"
					stroke="currentColor"
				>
					<path
						stroke-linecap="round"
						stroke-linejoin="round"
						stroke-width="2"
						d="M12 4.354a4 4 0 110 5.292M15 21H3v-1a6 6 0 0112 0v1zm0 0h6v-1a6 6 0 00-9-5.197M13 7a4 4 0 11-8 0 4 4 0 018 0z"
					/>
				</svg>
			</div>
			<p class="mb-4 flex-grow text-sm text-zinc-400">
				View and manage user accounts, reset passwords, and modify user roles.
			</p>
			<div class="flex justify-end">
				<span class="rounded-full bg-purple-900/20 px-3 py-1 text-xs font-medium text-purple-400"
					>Manage</span
				>
			</div>
		</a>

		<a
			href="/admin/settings"
			class="flex h-full flex-col rounded-xl border border-zinc-800 bg-zinc-900/70 p-6 shadow-md transition-colors duration-200 hover:bg-zinc-900"
		>
			<div class="mb-4 flex items-center justify-between">
				<h2 class="text-lg font-bold text-white">Site Settings</h2>
				<svg
					xmlns="http://www.w3.org/2000/svg"
					class="h-5 w-5 text-purple-500"
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
			</div>
			<p class="mb-4 flex-grow text-sm text-zinc-400">
				Configure global application settings like game version support and download links.
			</p>
			<div class="flex justify-end">
				<span class="rounded-full bg-zinc-800 px-3 py-1 text-xs font-medium text-zinc-400"
					>Coming Soon</span
				>
			</div>
		</a>

		<a
			href="/admin/faq"
			class="flex h-full flex-col rounded-xl border border-zinc-800 bg-zinc-900/70 p-6 shadow-md transition-colors duration-200 hover:bg-zinc-900"
		>
			<div class="mb-4 flex items-center justify-between">
				<h2 class="text-lg font-bold text-white">FAQ Management</h2>
				<svg
					xmlns="http://www.w3.org/2000/svg"
					class="h-5 w-5 text-purple-500"
					fill="none"
					viewBox="0 0 24 24"
					stroke="currentColor"
				>
					<path
						stroke-linecap="round"
						stroke-linejoin="round"
						stroke-width="2"
						d="M8.228 9c.549-1.165 2.03-2 3.772-2 2.21 0 4 1.343 4 3 0 1.4-1.278 2.575-3.006 2.907-.542.104-.994.54-.994 1.093m0 3h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
					/>
				</svg>
			</div>
			<p class="mb-4 flex-grow text-sm text-zinc-400">
				Manage frequently asked questions and their answers for the help center.
			</p>
			<div class="flex justify-end">
				<span class="rounded-full bg-purple-900/20 px-3 py-1 text-xs font-medium text-purple-400"
					>Manage</span
				>
			</div>
		</a>
	</div>
</div>
