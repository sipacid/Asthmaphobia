<script lang="ts">
	import { onMount } from 'svelte';
	import { scale } from 'svelte/transition';
	import { quintOut } from 'svelte/easing';

	// Visuals Category
	const visuals = [
		{
			name: 'Ghost ESP',
			description:
				'See ghosts through walls and across the map with customizable colors and distance indicators. Never be surprised by a ghost again.',
			iconPath: `M12 2c-4.4 0-8 3.6-8 8 0 5.3 7 11.5 7.3 11.8.2.1.5.2.7.2.2 0 .5-.1.7-.2.3-.3 7.3-6.5 7.3-11.8 0-4.4-3.6-8-8-8zm0 17.5c-2.1-2-6-6.3-6-9.5 0-3.3 2.7-6 6-6s6 2.7 6 6c0 3.2-3.9 7.5-6 9.5z M12 10a2.5 2.5 0 100-5 2.5 2.5 0 000 5z`,
			key_capabilities: [
				'Display ghost position through walls and objects',
				'Show distance to ghost in meters',
				'Customizable colors for different ghost states',
				'Filter by ghost type'
			]
		},
		{
			name: 'Player ESP',
			description:
				'Track your teammates through walls with player ESP. Displays player names, health status, and distance.',
			iconPath: `M12 12c2.21 0 4-1.79 4-4s-1.79-4-4-4-4 1.79-4 4 1.79 4 4 4zm0-6c1.1 0 2 .9 2 2s-.9 2-2 2-2-.9-2-2 .9-2 2-2zm0 7c-2.67 0-8 1.34-8 4v3h16v-3c0-2.66-5.33-4-8-4zm6 5H6v-.99c.2-.72 3.3-2.01 6-2.01s5.8 1.29 6 2v1z`,
			key_capabilities: [
				'See teammates through walls',
				'Display player health status',
				'Show distance to players',
				'Identify which items players are carrying'
			]
		},
		{
			name: 'Evidence ESP',
			description:
				'Locate all evidence items instantly, even through walls. Helps you gather evidence quickly without endless searching.',
			iconPath: `M14 11V8c0-1.11-.89-2-2-2h-1V3H9v3H8c-1.11 0-2 .89-2 2v3H3v7c0 1.11.89 2 2 2h14c1.11 0 2-.89 2-2v-7h-7zm-9 7c-.55 0-1-.45-1-1v-5h2v6H5zm14-1c0 .55-.45 1-1 1h-9v-6h10v5z M8.5 14.5a1.5 1.5 0 100-3 1.5 1.5 0 000 3z M15.5 14.5a1.5 1.5 0 100-3 1.5 1.5 0 000 3z`,
			key_capabilities: [
				'See all evidence through walls',
				'Categorized by evidence type',
				'Display distance to evidence',
				'Highlight relevant evidence for your current ghost'
			]
		},
		{
			name: 'Fusebox ESP',
			description:
				'Easily locate fuseboxes throughout the map. Never stumble around in the dark looking for power again.',
			iconPath: `M7 21h10v-1H7v1zM7 3v1h10V3H7z M17 6H7c-1.1 0-2 .9-2 2v8c0 1.1.9 2 2 2h10c1.1 0 2-.9 2-2V8c0-1.1-.9-2-2-2zm-1 10H8c-.55 0-1-.45-1-1V9c0-.55.45-1 1-1h8c.55 0 1 .45 1 1v6c0 .55-.45 1-1 1z M12 10c-1.1 0-2 .9-2 2s.9 2 2 2 2-.9 2-2-.9-2-2-2z`,
			key_capabilities: [
				'Display fusebox locations through walls',
				'Show power status (on/off)',
				'Indicate distance to fusebox',
				'Highlight when ghost interacts with electricity'
			]
		},
		{
			name: 'Ghost Info Window',
			description:
				'Detailed real-time information about the ghost including type, behavior, current activity, and hunting status.',
			iconPath: `M19 3H5c-1.1 0-2 .9-2 2v14c0 1.1.9 2 2 2h14c1.1 0 2-.9 2-2V5c0-1.1-.9-2-2-2zm0 16H5V5h14v14z M14.5 11.5c0 2-2.5 3.5-2.5 5h-2c0-1.5-2.5-3-2.5-5C7.5 9.57 9.07 8 11 8s3.5 1.57 3.5 3.5zm-2.5 6h-2v-2h2v2z`,
			key_capabilities: [
				'Real-time ghost type identification',
				'Hunt countdown timer',
				'Ghost activity monitoring',
				'Evidence tracking and suggestions'
			]
		},
		{
			name: 'Watermark',
			description: 'Subtle, customizable watermark to show cheat version and status.',
			iconPath: `M22 18v-2H8V4h2L7 1 4 4h2v2H2v2h4v8c0 1.1.9 2 2 2h8v2h-2l3 3 3-3h-2v-2h4zM10 8h6v6h2V8c0-1.1-.9-2-2-2h-6v2z`,
			key_capabilities: [
				'Customizable position',
				'Version information display',
				'FPS counter option',
				'Status indicators for active features'
			]
		}
	];

	// Movement Category
	const movement = [
		{
			name: 'NoClip',
			description:
				'Walk through walls, doors, and any objects. Explore the map freely without physical constraints.',
			iconPath: `M17 20.41L18.41 19 15 15.59 13.59 17 17 20.41zM7.5 8H11v5.59L5.59 19 7 20.41l6-6V8h3.5L12 3.5 7.5 8z`,
			key_capabilities: [
				'Pass through all physical obstacles',
				'Adjustable clipping speed',
				'Toggle-based activation',
				'Works during hunts and events'
			]
		},
		{
			name: 'Speed Hack',
			description:
				'Dramatically increase your movement speed. Configure multiple speed presets for different situations.',
			iconPath: `M13.49 5.48c1.1 0 2-.9 2-2s-.9-2-2-2-2 .9-2 2 .9 2 2 2zm-3.6 13.9l1-4.4 2.1 2v6h2v-7.5l-2.1-2 .6-3c1.3 1.5 3.3 2.5 5.5 2.5v-2c-1.9 0-3.5-1-4.3-2.4l-1-1.6c-.4-.6-1-1-1.7-1-.3 0-.5.1-.8.1l-5.2 2.2v4.7h2v-3.4l1.8-.7-1.6 8.1-4.9-1-.4 2 7 1.4z`,
			key_capabilities: [
				'Multiple speed multiplier presets (2x, 3x, 5x, 10x)',
				'Configurable acceleration',
				'Works with all movement types',
				'Silent speed mode to avoid detection'
			]
		},
		{
			name: 'Teleport',
			description:
				'Instantly teleport to locations of interest, including ghosts, evidence, team members, or custom coordinates.',
			iconPath: `M5 9h14v6h-14z M21 3H3c-1.1 0-2 .9-2 2v14c0 1.1.9 2 2 2h18c1.1 0 2-.9 2-2V5c0-1.1-.9-2-2-2zm0 16H3V5h18v14z M15 15l-6-2.5V10l6-2.5z`,
			key_capabilities: [
				'Teleport to ghost location',
				'Teleport to team members',
				'Teleport to evidence items',
				'Save and load custom teleport positions'
			]
		},
		{
			name: 'Infinite Stamina',
			description:
				'Never run out of stamina. Sprint indefinitely without slowing down or stopping to catch your breath.',
			iconPath: `M17 12c-2.76 0-5 2.24-5 5s2.24 5 5 5 5-2.24 5-5-2.24-5-5-5zm0 8c-1.65 0-3-1.35-3-3s1.35-3 3-3 3 1.35 3 3-1.35 3-3 3z M4 9h5c.55 0 1 .45 1 1v5c0 .55-.45 1-1 1H4c-.55 0-1-.45-1-1v-5c0-.55.45-1 1-1z M12 8V6c0-1.1-.9-2-2-2H6c-1.1 0-2 .9-2 2v6c0 1.1.9 2 2 2h2v2c0 1.1.9 2 2 2h6c1.1 0 2-.9 2-2v-4c0-1.1-.9-2-2-2h-4z`,
			key_capabilities: [
				'Unlimited sprint duration',
				'No stamina drain',
				'Consistent movement speed',
				'Works in all game modes'
			]
		}
	];

	// Player Modifications Category
	const players = [
		{
			name: 'God Mode',
			description:
				'Complete invulnerability to ghost attacks and environmental damage. Play without fear of death.',
			iconPath: `M11.99 2C6.47 2 2 6.48 2 12s4.47 10 9.99 10C17.52 22 22 17.52 22 12S17.52 2 11.99 2zm4.24 16L12 15.45 7.77 18l1.12-4.81-3.73-3.23 4.92-.42L12 5l1.92 4.53 4.92.42-3.73 3.23L16.23 18z`,
			key_capabilities: [
				'Immunity to ghost attacks',
				'Sanity protection',
				'No environmental damage',
				'Optional death animation bypass'
			]
		},
		{
			name: 'Player Modifier',
			description:
				'Modify player stats including sanity, speed, reach distance, and more. Fully customize your character for optimal gameplay.',
			iconPath: `M17.66 7.93L12 2.27 6.34 7.93c-3.12 3.12-3.12 8.19 0 11.31C7.9 20.8 9.95 21.58 12 21.58c2.05 0 4.1-.78 5.66-2.34 3.12-3.12 3.12-8.19 0-11.31zM12 19.59c-1.6 0-3.11-.62-4.24-1.76C6.62 16.69 6 15.19 6 13.59s.62-3.11 1.76-4.24L12 5.1v14.49z`,
			key_capabilities: [
				'Adjust sanity levels',
				'Modify player size/hitbox',
				'Change interaction reach distance',
				'Control footstep sound volume'
			]
		}
	];

	// Ghost Category
	const ghost = [
		{
			name: 'Ghost Modifier',
			description:
				'Control and modify ghost behavior, speed, visibility and other attributes. Make ghosts more predictable or more challenging.',
			iconPath: `M12 2c-5.33 4-8 8.27-8 12 0 4.42 3.58 8 8 8s8-3.58 8-8c0-3.73-2.67-8-8-12zm0 18c-3.31 0-6-2.69-6-6 0-1 0-3 4-3 2 0 2 4 2 4s.67-4 4-4c3 0 4 2 4 3 0 3.31-2.69 6-6 6z`,
			key_capabilities: [
				'Adjust ghost speed',
				'Modify ghost visibility',
				'Control hunt duration',
				'Change ghost behavior patterns'
			]
		},
		{
			name: 'Ghost Interactor',
			description:
				'Directly interact with the ghost to force events, hunts, or specific behaviors. Control the ghost like a puppet master.',
			iconPath: `M18 11l5-5-1.41-1.41L16 10.17V3h-2v7.17L8.41 4.59 7 6l5 5-5 5 1.41 1.41L14 11.83V19h2v-7.17l5.59 5.59L23 16l-5-5z`,
			key_capabilities: [
				'Force ghost events',
				'Trigger or stop hunts',
				'Make the ghost respond to specific questions',
				'Direct ghost to specific locations'
			]
		}
	];

	// Cursed Items Category
	const cursedItems = [
		{
			name: 'Cursed Item Modifier',
			description:
				'Modify and control cursed items behavior. Use ouija boards without sanity loss, control monkey paws, and more.',
			iconPath: `M11 14h2v-3h3V9h-3V6h-2v3H8v2h3z M21 5h-3.17l-1.24-1.35c-.37-.41-.91-.65-1.47-.65H8.88c-.56 0-1.1.24-1.48.65L6.17 5H3c-1.1 0-2 .9-2 2v12c0 1.1.9 2 2 2h18c1.1 0 2-.9 2-2V7c0-1.1-.9-2-2-2zm-3 12H6c-.55 0-1-.45-1-1V8c0-.55.45-1 1-1h12c.55 0 1 .45 1 1v8c0 .55-.45 1-1 1z`,
			key_capabilities: [
				'Use cursed items without sanity drain',
				'Unlimited cursed item uses',
				'Prevent negative effects',
				'Force positive outcomes'
			]
		},
		{
			name: 'Force Card',
			description:
				'Force specific tarot card draws from the deck. Get the exact cards you want every time.',
			iconPath: `M17 3H7c-1.1 0-2 .9-2 2v14c0 1.1.9 2 2 2h10c1.1 0 2-.9 2-2V5c0-1.1-.9-2-2-2zm-1 16H8c-.55 0-1-.45-1-1V6c0-.55.45-1 1-1h8c.55 0 1 .45 1 1v12c0 .55-.45 1-1 1z M10 7l5 5-5 5V7z`,
			key_capabilities: [
				'Select specific tarot cards to draw',
				'Preview upcoming cards',
				'Reset the deck at will',
				'Customize card effects'
			]
		}
	];

	// Miscellaneous Category
	const miscellaneous = [
		{
			name: 'Anti-Kick',
			description:
				'Prevent being kicked from lobbies. Stay in the game even if the host tries to remove you.',
			iconPath: `M12 1L3 5v6c0 5.55 3.84 10.74 9 12 5.16-1.26 9-6.45 9-12V5l-9-4zm0 10.99h7c-.53 4.12-3.28 7.79-7 8.94V12H5V6.3l7-3.11v8.8z`,
			key_capabilities: [
				'Block kick attempts',
				'Prevent lobby disconnection',
				'Rejoin mechanics if kicked',
				'Stealth mode to hide from host'
			]
		},
		{
			name: 'Custom Name',
			description:
				'Use any name in the game, including special characters, colors, and styles that would normally be restricted.',
			iconPath: `M14.06 9.02l.92.92L5.92 19H5v-.92l9.06-9.06M17.66 3c-.25 0-.51.1-.7.29l-1.83 1.83 3.75 3.75 1.83-1.83c.39-.39.39-1.02 0-1.41l-2.34-2.34c-.2-.2-.45-.29-.71-.29zm-3.6 3.19L3 17.25V21h3.75L17.81 9.94l-3.75-3.75z`,
			key_capabilities: [
				'Use special characters',
				'Apply custom colors to name',
				'Bypass name filters',
				'Save multiple name presets'
			]
		},
		{
			name: 'Door Modifier',
			description:
				'Control all doors remotely. Lock or unlock doors, open or close them from anywhere in the map.',
			iconPath: `M19 19V5c0-1.1-.9-2-2-2H7c-1.1 0-2 .9-2 2v14H3v2h18v-2h-2zm-2 0H7V5h10v14z M9 11h2v2H9z`,
			key_capabilities: [
				'Remotely open/close any door',
				'Lock doors during hunts',
				'Prevent ghosts from interacting with doors',
				'Door interaction aura visible through walls'
			]
		},
		{
			name: 'Free Mouse Look',
			description:
				'Look around freely while holding items or during events when normal camera movement is restricted.',
			iconPath: `M12 4.5C7 4.5 2.73 7.61 1 12c1.73 4.39 6 7.5 11 7.5s9.27-3.11 11-7.5c-1.73-4.39-6-7.5-11-7.5zM12 17c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5zm0-8c-1.66 0-3 1.34-3 3s1.34 3 3 3 3-1.34 3-3-1.34-3-3-3z`,
			key_capabilities: [
				'Free camera rotation while carrying items',
				'Look around during immobilizing events',
				'Increased field of view option',
				'Smooth camera movement option'
			]
		},
		{
			name: 'Leave People',
			description:
				'Leave the mission while keeping your friends stranded in the game. Great for trolling or emergency exits.',
			iconPath: `M10.09 15.59L11.5 17l5-5-5-5-1.41 1.41L12.67 11H3v2h9.67l-2.58 2.59zM19 3H5c-1.11 0-2 .9-2 2v4h2V5h14v14H5v-4H3v4c0 1.1.89 2 2 2h14c1.1 0 2-.9 2-2V5c0-1.1-.9-2-2-2z`,
			key_capabilities: [
				'Exit mission while the team remains',
				'Preserve items and rewards on exit',
				'Reconnect option if desired',
				'Invisible mode option before leaving'
			]
		},
		{
			name: 'Reward Modifier',
			description: 'Increase mission rewards. Get more cash and XP after completing objectives.',
			iconPath: `M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm1.41 16.09V20h-2.67v-1.93c-1.71-.36-3.16-1.46-3.27-3.4h1.96c.1 1.05.82 1.87 2.65 1.87 1.96 0 2.4-.98 2.4-1.59 0-.83-.44-1.61-2.67-2.14-2.48-.6-4.18-1.62-4.18-3.67 0-1.72 1.39-2.84 3.11-3.21V4h2.67v1.95c1.86.45 2.79 1.86 2.85 3.39H14.3c-.05-1.11-.64-1.87-2.22-1.87-1.5 0-2.4.68-2.4 1.64 0 .84.65 1.39 2.67 1.91s4.18 1.39 4.18 3.91c-.01 1.83-1.38 2.83-3.12 3.16z`,
			key_capabilities: [
				'Multiply cash rewards',
				'Increase XP gains',
				'Modify objective rewards individually',
				'Guarantee photo rewards'
			]
		}
	];

	// Animation
	let headerAnimated = $state(false);

	onMount(() => {
		setTimeout(() => {
			headerAnimated = true;
		}, 300);
	});

	// Feature detail modal functionality
	let selectedFeature = $state(null);
	let showModal = $state(false);

	function openFeatureModal(feature) {
		selectedFeature = feature;
		showModal = true;
	}

	function closeFeatureModal() {
		showModal = false;
		setTimeout(() => {
			selectedFeature = null;
		}, 300);
	}

	// Handle clicking outside modal to close
	function handleModalBackgroundClick(event) {
		if (event.target === event.currentTarget) {
			closeFeatureModal();
		}
	}
</script>

<svelte:head>
	<title>Features - Asthmaphobia Cheat</title>
	<meta
		name="description"
		content="Explore all the powerful features of Asthmaphobia Cheat for Phasmophobia"
	/>
</svelte:head>

<!-- Feature detail modal -->
{#if showModal}
	<div
		class={`fixed inset-0 z-50 flex items-center justify-center backdrop-blur-sm transition-all duration-300 ${showModal ? 'bg-black/70 opacity-100' : 'opacity-0'}`}
		onclick={handleModalBackgroundClick}
		role="dialog"
		aria-modal="true"
	>
		{#if selectedFeature}
			<div
				class={`relative max-h-[90vh] w-full max-w-3xl overflow-y-auto rounded-xl border border-zinc-700 bg-zinc-900/95 p-6 shadow-xl transition-all duration-300 ${showModal ? 'scale-100 opacity-100' : 'scale-90 opacity-0'}`}
				transition:scale={{ start: 0.95, duration: 250, easing: quintOut }}
			>
				<button
					class="absolute top-4 right-4 rounded-full p-2 text-zinc-500 transition-colors hover:bg-zinc-800 hover:text-zinc-300"
					onclick={closeFeatureModal}
					aria-label="Close modal"
				>
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
							d="M6 18L18 6M6 6l12 12"
						/>
					</svg>
				</button>

				<div class="flex items-start">
					<div
						class="mr-4 flex h-12 w-12 flex-shrink-0 items-center justify-center rounded-xl bg-purple-900/40"
					>
						<svg
							xmlns="http://www.w3.org/2000/svg"
							class="h-7 w-7 text-purple-400"
							viewBox="0 0 24 24"
							fill="none"
							stroke="currentColor"
							stroke-width="1.5"
							stroke-linecap="round"
							stroke-linejoin="round"
						>
							<path d={selectedFeature.iconPath} />
						</svg>
					</div>
					<div>
						<h3 class="mb-2 text-xl font-bold text-white">{selectedFeature.name}</h3>
						<p class="mb-4 text-zinc-300">{selectedFeature.description}</p>
					</div>
				</div>

				<div class="mt-6 mb-4">
					<h4 class="mb-3 font-medium text-purple-400">Key Capabilities</h4>
					<ul class="space-y-1">
						{#each selectedFeature.key_capabilities as capability (capability)}
							<li class="flex items-start">
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="mt-1 mr-2 h-4 w-4 flex-shrink-0 text-purple-500"
									fill="none"
									viewBox="0 0 24 24"
									stroke="currentColor"
								>
									<path
										stroke-linecap="round"
										stroke-linejoin="round"
										stroke-width="2"
										d="M5 13l4 4L19 7"
									/>
								</svg>
								<span class="text-zinc-300">{capability}</span>
							</li>
						{/each}
					</ul>
				</div>
			</div>
		{/if}
	</div>
{/if}

<div class="min-h-screen bg-black">
	<div class="relative">
		<div
			class="absolute inset-0 bg-gradient-to-b from-purple-900/20 via-transparent to-transparent opacity-60"
		></div>
		<div class="relative z-10 container mx-auto max-w-6xl px-4 py-8">
			<!-- Header Section -->
			<section class="pt-16 pb-12">
				<div
					class="mb-12 rounded-3xl border border-zinc-800/40 bg-zinc-900/70 p-8 shadow-xl backdrop-blur-md"
				>
					<div
						class="mb-4 inline-block rounded-full bg-gradient-to-r from-purple-500/20 to-purple-700/20 px-4 py-1.5 backdrop-blur-sm"
					>
						<span class="text-sm font-medium text-purple-300">Feature Overview</span>
					</div>

					<h1 class="mb-4 text-4xl font-bold text-white md:text-5xl">
						<span
							class="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent"
						>
							All Features
						</span>
					</h1>

					<p
						class="max-w-xl text-lg text-zinc-300 transition-all delay-200 duration-700"
						class:opacity-100={headerAnimated}
						class:translate-y-0={headerAnimated}
						class:opacity-0={!headerAnimated}
						class:translate-y-4={!headerAnimated}
					>
						Explore the complete set of features available in Asthmaphobia. Every tool you need to
						master Phasmophobia.
					</p>
				</div>

				<div class="mb-6 flex flex-wrap gap-2 pb-2">
					<a
						href="#visuals"
						class="rounded-full bg-purple-900/30 px-4 py-2 text-sm font-medium text-purple-300 backdrop-blur-sm transition-colors hover:bg-purple-800/30"
					>
						Visuals
					</a>
					<a
						href="#movement"
						class="rounded-full bg-purple-900/30 px-4 py-2 text-sm font-medium text-purple-300 backdrop-blur-sm transition-colors hover:bg-purple-800/30"
					>
						Movement
					</a>
					<a
						href="#players"
						class="rounded-full bg-purple-900/30 px-4 py-2 text-sm font-medium text-purple-300 backdrop-blur-sm transition-colors hover:bg-purple-800/30"
					>
						Player Mods
					</a>
					<a
						href="#ghost"
						class="rounded-full bg-purple-900/30 px-4 py-2 text-sm font-medium text-purple-300 backdrop-blur-sm transition-colors hover:bg-purple-800/30"
					>
						Ghost Controls
					</a>
					<a
						href="#cursed"
						class="rounded-full bg-purple-900/30 px-4 py-2 text-sm font-medium text-purple-300 backdrop-blur-sm transition-colors hover:bg-purple-800/30"
					>
						Cursed Items
					</a>
					<a
						href="#misc"
						class="rounded-full bg-purple-900/30 px-4 py-2 text-sm font-medium text-purple-300 backdrop-blur-sm transition-colors hover:bg-purple-800/30"
					>
						Miscellaneous
					</a>
				</div>
			</section>

			<!-- Visual Features -->
			<section id="visuals" class="mb-20 scroll-mt-24">
				<div class="mb-8 flex items-center">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-3 h-7 w-7 text-purple-500"
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
					<h2 class="text-3xl font-bold text-white">Visual Features</h2>
				</div>

				<p class="mb-8 text-lg text-zinc-400">
					See everything in the game with our advanced visual mods. From ghosts to evidence, nothing
					will remain hidden.
				</p>

				<div class="grid gap-6 md:grid-cols-2 lg:grid-cols-3">
					{#each visuals as feature (feature.name)}
						<button
							class="group relative cursor-pointer overflow-hidden rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 text-left backdrop-blur-sm transition-all duration-300 hover:border-purple-600/30 hover:bg-zinc-900/70"
							onclick={() => openFeatureModal(feature)}
							tabindex="0"
						>
							<div
								class="mb-4 flex h-14 w-14 items-center justify-center rounded-xl bg-gradient-to-br from-purple-900/40 to-indigo-900/40 p-3 transition-colors duration-300 group-hover:from-purple-700/40 group-hover:to-indigo-600/40"
							>
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="h-full w-full text-purple-400 transition-colors duration-300 group-hover:text-purple-300"
									viewBox="0 0 24 24"
									fill="none"
									stroke="currentColor"
									stroke-width="1.5"
									stroke-linecap="round"
									stroke-linejoin="round"
								>
									<path d={feature.iconPath} />
								</svg>
							</div>
							<div class="relative z-10">
								<h3 class="mb-2 text-lg font-medium text-white">{feature.name}</h3>
								<p class="mb-4 text-sm text-zinc-400">{feature.description}</p>
								<div
									class="flex items-center text-xs font-medium text-purple-400 transition-colors group-hover:text-purple-300"
								>
									View Details
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="ml-1 h-4 w-4"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M9 5l7 7-7 7"
										/>
									</svg>
								</div>
							</div>
						</button>
					{/each}
				</div>
			</section>

			<!-- Movement Features -->
			<section id="movement" class="mb-20 scroll-mt-24">
				<div class="mb-8 flex items-center">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-3 h-7 w-7 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M13 10V3L4 14h7v7l9-11h-7z"
						/>
					</svg>
					<h2 class="text-3xl font-bold text-white">Movement Features</h2>
				</div>

				<p class="mb-8 text-lg text-zinc-400">
					Move faster, ignore obstacles, and teleport across the map with our movement enhancement
					features.
				</p>

				<div class="grid gap-6 md:grid-cols-2 lg:grid-cols-2">
					{#each movement as feature (feature.name)}
						<button
							class="group relative cursor-pointer overflow-hidden rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 text-left backdrop-blur-sm transition-all duration-300 hover:border-purple-600/30 hover:bg-zinc-900/70"
							onclick={() => openFeatureModal(feature)}
							tabindex="0"
						>
							<div
								class="mb-4 flex h-14 w-14 items-center justify-center rounded-xl bg-gradient-to-br from-purple-900/40 to-indigo-900/40 p-3 transition-colors duration-300 group-hover:from-purple-700/40 group-hover:to-indigo-600/40"
							>
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="h-full w-full text-purple-400 transition-colors duration-300 group-hover:text-purple-300"
									viewBox="0 0 24 24"
									fill="none"
									stroke="currentColor"
									stroke-width="1.5"
									stroke-linecap="round"
									stroke-linejoin="round"
								>
									<path d={feature.iconPath} />
								</svg>
							</div>
							<div class="relative z-10">
								<h3 class="mb-2 text-lg font-medium text-white">{feature.name}</h3>
								<p class="mb-4 text-sm text-zinc-400">{feature.description}</p>
								<div
									class="flex items-center text-xs font-medium text-purple-400 transition-colors group-hover:text-purple-300"
								>
									View Details
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="ml-1 h-4 w-4"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M9 5l7 7-7 7"
										/>
									</svg>
								</div>
							</div>
						</button>
					{/each}
				</div>
			</section>

			<!-- Player Modifications -->
			<section id="players" class="mb-20 scroll-mt-24">
				<div class="mb-8 flex items-center">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-3 h-7 w-7 text-purple-500"
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
					<h2 class="text-3xl font-bold text-white">Player Modifications</h2>
				</div>

				<p class="mb-8 text-lg text-zinc-400">
					Enhance your player character with god mode, stat modifications and other powerful
					abilities.
				</p>

				<div class="grid gap-6 md:grid-cols-2 lg:grid-cols-2">
					{#each players as feature (feature.name)}
						<button
							class="group relative cursor-pointer overflow-hidden rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 text-left backdrop-blur-sm transition-all duration-300 hover:border-purple-600/30 hover:bg-zinc-900/70"
							onclick={() => openFeatureModal(feature)}
							tabindex="0"
						>
							<div
								class="mb-4 flex h-14 w-14 items-center justify-center rounded-xl bg-gradient-to-br from-purple-900/40 to-indigo-900/40 p-3 transition-colors duration-300 group-hover:from-purple-700/40 group-hover:to-indigo-600/40"
							>
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="h-full w-full text-purple-400 transition-colors duration-300 group-hover:text-purple-300"
									viewBox="0 0 24 24"
									fill="none"
									stroke="currentColor"
									stroke-width="1.5"
									stroke-linecap="round"
									stroke-linejoin="round"
								>
									<path d={feature.iconPath} />
								</svg>
							</div>
							<div class="relative z-10">
								<h3 class="mb-2 text-lg font-medium text-white">{feature.name}</h3>
								<p class="mb-4 text-sm text-zinc-400">{feature.description}</p>
								<div
									class="flex items-center text-xs font-medium text-purple-400 transition-colors group-hover:text-purple-300"
								>
									View Details
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="ml-1 h-4 w-4"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M9 5l7 7-7 7"
										/>
									</svg>
								</div>
							</div>
						</button>
					{/each}
				</div>
			</section>

			<!-- Ghost Controls -->
			<section id="ghost" class="mb-20 scroll-mt-24">
				<div class="mb-8 flex items-center">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-3 h-7 w-7 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M9.663 17h4.673M12 3v1m6.364 1.636l-.707.707M21 12h-1M4 12H3m3.343-5.657l-.707-.707m2.828 9.9a5 5 0 117.072 0l-.548.547A3.374 3.374 0 0014 18.469V19a2 2 0 11-4 0v-.531c0-.895-.356-1.754-.988-2.386l-.548-.547z"
						/>
					</svg>
					<h2 class="text-3xl font-bold text-white">Ghost Controls</h2>
				</div>

				<p class="mb-8 text-lg text-zinc-400">
					Take control of the ghost with our powerful ghost modification features. Force hunts,
					change behavior, and more.
				</p>

				<div class="grid gap-6 md:grid-cols-2 lg:grid-cols-2">
					{#each ghost as feature (feature.name)}
						<button
							class="group relative cursor-pointer overflow-hidden rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 text-left backdrop-blur-sm transition-all duration-300 hover:border-purple-600/30 hover:bg-zinc-900/70"
							onclick={() => openFeatureModal(feature)}
							tabindex="0"
						>
							<div
								class="mb-4 flex h-14 w-14 items-center justify-center rounded-xl bg-gradient-to-br from-purple-900/40 to-indigo-900/40 p-3 transition-colors duration-300 group-hover:from-purple-700/40 group-hover:to-indigo-600/40"
							>
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="h-full w-full text-purple-400 transition-colors duration-300 group-hover:text-purple-300"
									viewBox="0 0 24 24"
									fill="none"
									stroke="currentColor"
									stroke-width="1.5"
									stroke-linecap="round"
									stroke-linejoin="round"
								>
									<path d={feature.iconPath} />
								</svg>
							</div>
							<div class="relative z-10">
								<h3 class="mb-2 text-lg font-medium text-white">{feature.name}</h3>
								<p class="mb-4 text-sm text-zinc-400">{feature.description}</p>
								<div
									class="flex items-center text-xs font-medium text-purple-400 transition-colors group-hover:text-purple-300"
								>
									View Details
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="ml-1 h-4 w-4"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M9 5l7 7-7 7"
										/>
									</svg>
								</div>
							</div>
						</button>
					{/each}
				</div>
			</section>

			<!-- Cursed Items -->
			<section id="cursed" class="mb-20 scroll-mt-24">
				<div class="mb-8 flex items-center">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-3 h-7 w-7 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M5 3v4M3 5h4M6 17v4m-2-2h4m5-16l2.286 6.857L21 12l-5.714 2.143L13 21l-2.286-6.857L5 12l5.714-2.143L13 3z"
						/>
					</svg>
					<h2 class="text-3xl font-bold text-white">Cursed Items</h2>
				</div>

				<p class="mb-8 text-lg text-zinc-400">
					Manipulate and control cursed items in the game. Gain advantages without suffering the
					consequences.
				</p>

				<div class="grid gap-6 md:grid-cols-2 lg:grid-cols-2">
					{#each cursedItems as feature (feature.name)}
						<button
							class="group relative cursor-pointer overflow-hidden rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 text-left backdrop-blur-sm transition-all duration-300 hover:border-purple-600/30 hover:bg-zinc-900/70"
							onclick={() => openFeatureModal(feature)}
							tabindex="0"
						>
							<div
								class="mb-4 flex h-14 w-14 items-center justify-center rounded-xl bg-gradient-to-br from-purple-900/40 to-indigo-900/40 p-3 transition-colors duration-300 group-hover:from-purple-700/40 group-hover:to-indigo-600/40"
							>
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="h-full w-full text-purple-400 transition-colors duration-300 group-hover:text-purple-300"
									viewBox="0 0 24 24"
									fill="none"
									stroke="currentColor"
									stroke-width="1.5"
									stroke-linecap="round"
									stroke-linejoin="round"
								>
									<path d={feature.iconPath} />
								</svg>
							</div>
							<div class="relative z-10">
								<h3 class="mb-2 text-lg font-medium text-white">{feature.name}</h3>
								<p class="mb-4 text-sm text-zinc-400">{feature.description}</p>
								<div
									class="flex items-center text-xs font-medium text-purple-400 transition-colors group-hover:text-purple-300"
								>
									View Details
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="ml-1 h-4 w-4"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M9 5l7 7-7 7"
										/>
									</svg>
								</div>
							</div>
						</button>
					{/each}
				</div>
			</section>

			<!-- Miscellaneous Features -->
			<section id="misc" class="mb-20 scroll-mt-24">
				<div class="mb-8 flex items-center">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-3 h-7 w-7 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M12 6V4m0 2a2 2 0 100 4m0-4a2 2 0 110 4m-6 8a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4m6 6v10m6-2a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4"
						/>
					</svg>
					<h2 class="text-3xl font-bold text-white">Miscellaneous Features</h2>
				</div>

				<p class="mb-8 text-lg text-zinc-400">
					Additional powerful tools and utilities to enhance your Phasmophobia experience in various
					ways.
				</p>

				<div class="grid gap-6 md:grid-cols-2 lg:grid-cols-3">
					{#each miscellaneous as feature (feature.name)}
						<button
							class="group relative cursor-pointer overflow-hidden rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 text-left backdrop-blur-sm transition-all duration-300 hover:border-purple-600/30 hover:bg-zinc-900/70"
							onclick={() => openFeatureModal(feature)}
							tabindex="0"
						>
							<div
								class="mb-4 flex h-14 w-14 items-center justify-center rounded-xl bg-gradient-to-br from-purple-900/40 to-indigo-900/40 p-3 transition-colors duration-300 group-hover:from-purple-700/40 group-hover:to-indigo-600/40"
							>
								<svg
									xmlns="http://www.w3.org/2000/svg"
									class="h-full w-full text-purple-400 transition-colors duration-300 group-hover:text-purple-300"
									viewBox="0 0 24 24"
									fill="none"
									stroke="currentColor"
									stroke-width="1.5"
									stroke-linecap="round"
									stroke-linejoin="round"
								>
									<path d={feature.iconPath} />
								</svg>
							</div>
							<div class="relative z-10">
								<h3 class="mb-2 text-lg font-medium text-white">{feature.name}</h3>
								<p class="mb-4 text-sm text-zinc-400">{feature.description}</p>
								<div
									class="flex items-center text-xs font-medium text-purple-400 transition-colors group-hover:text-purple-300"
								>
									View Details
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="ml-1 h-4 w-4"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M9 5l7 7-7 7"
										/>
									</svg>
								</div>
							</div>
						</button>
					{/each}
				</div>
			</section>

			<!-- Feature Comparison -->
			<section class="mb-16">
				<div class="mb-8 flex items-center">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						class="mr-3 h-7 w-7 text-purple-500"
						fill="none"
						viewBox="0 0 24 24"
						stroke="currentColor"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M9 19v-6a2 2 0 00-2-2H5a2 2 0 00-2 2v6a2 2 0 002 2h2a2 2 0 002-2zm0 0V9a2 2 0 012-2h2a2 2 0 012 2v10m-6 0a2 2 0 002 2h2a2 2 0 002-2m0 0V5a2 2 0 012-2h2a2 2 0 012 2v14a2 2 0 01-2 2h-2a2 2 0 01-2-2z"
						/>
					</svg>
					<h2 class="text-3xl font-bold text-white">Feature Categories</h2>
				</div>

				<p class="mb-8 text-lg text-zinc-400">
					See how our features are organized to provide the most comprehensive Phasmophobia cheat
					experience.
				</p>

				<div class="overflow-x-auto">
					<table
						class="w-full rounded-xl border border-zinc-800/50 bg-zinc-900/30 backdrop-blur-sm"
					>
						<thead>
							<tr class="border-b border-zinc-800/70">
								<th class="p-4 text-left text-white">Category</th>
								<th class="p-4 text-left text-white">Features</th>
								<th class="p-4 text-left text-white">Description</th>
							</tr>
						</thead>
						<tbody>
							<tr class="border-b border-zinc-800/30">
								<td class="p-4 font-medium text-purple-400">Visuals</td>
								<td class="p-4 text-zinc-300">{visuals.length} features</td>
								<td class="p-4 text-zinc-400"
									>ESP and visual enhancements to see everything in the game</td
								>
							</tr>
							<tr class="border-b border-zinc-800/30">
								<td class="p-4 font-medium text-purple-400">Movement</td>
								<td class="p-4 text-zinc-300">{movement.length} features</td>
								<td class="p-4 text-zinc-400"
									>NoClip, speed, and teleportation features for effortless navigation</td
								>
							</tr>
							<tr class="border-b border-zinc-800/30">
								<td class="p-4 font-medium text-purple-400">Players</td>
								<td class="p-4 text-zinc-300">{players.length} features</td>
								<td class="p-4 text-zinc-400"
									>Player stat modifications and invulnerability options</td
								>
							</tr>
							<tr class="border-b border-zinc-800/30">
								<td class="p-4 font-medium text-purple-400">Ghost</td>
								<td class="p-4 text-zinc-300">{ghost.length} features</td>
								<td class="p-4 text-zinc-400"
									>Control ghost behavior and interact with the entity directly</td
								>
							</tr>
							<tr class="border-b border-zinc-800/30">
								<td class="p-4 font-medium text-purple-400">Cursed Items</td>
								<td class="p-4 text-zinc-300">{cursedItems.length} features</td>
								<td class="p-4 text-zinc-400"
									>Modify and control cursed items' effects and behavior</td
								>
							</tr>
							<tr>
								<td class="p-4 font-medium text-purple-400">Miscellaneous</td>
								<td class="p-4 text-zinc-300">{miscellaneous.length} features</td>
								<td class="p-4 text-zinc-400"
									>Other utilities including anti-kick, door control, and more</td
								>
							</tr>
						</tbody>
					</table>
				</div>
			</section>

			<!-- CTA Section -->
			<section class="mb-4">
				<div class="relative overflow-hidden rounded-3xl border border-zinc-800/40">
					<div
						class="absolute inset-0 bg-gradient-to-r from-purple-900/20 to-blue-900/20 opacity-30"
					></div>
					<div class="absolute -inset-[500px] -z-10">
						<div
							class="absolute top-1/3 left-1/3 h-[600px] w-[600px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-purple-500/20 blur-[100px]"
						></div>
					</div>

					<div class="relative z-10 p-10 text-center md:p-16">
						<h2 class="mb-6 text-3xl font-bold text-white md:text-4xl">
							Ready to Experience These Features?
						</h2>
						<p class="mx-auto mb-8 max-w-2xl text-lg text-zinc-300">
							Join ghost hunters who are already using Asthmaphobia to enhance their Phasmophobia
							experience.
						</p>

						<div class="flex flex-col items-center justify-center gap-4 sm:flex-row">
							<a
								href="/dashboard"
								class="group relative overflow-hidden rounded-xl bg-gradient-to-r from-purple-600 to-indigo-600 px-8 py-4 text-center font-medium text-white shadow-lg transition-all hover:from-purple-500 hover:to-indigo-500 focus:ring-2 focus:ring-purple-500 focus:ring-offset-2 focus:ring-offset-black focus:outline-none"
							>
								<div class="relative z-10 flex items-center justify-center">
									<svg
										xmlns="http://www.w3.org/2000/svg"
										class="mr-2 h-5 w-5"
										fill="none"
										viewBox="0 0 24 24"
										stroke="currentColor"
									>
										<path
											stroke-linecap="round"
											stroke-linejoin="round"
											stroke-width="2"
											d="M4 16v1a3 3 0 003 3h10a3 3 0 003-3v-1m-4-4l-4 4m0 0l-4-4m4 4V4"
										/>
									</svg>
									Download Now
								</div>
								<div
									class="absolute inset-0 -translate-y-full bg-gradient-to-r from-purple-600/30 to-indigo-600/30 transition-transform duration-300 ease-out group-hover:translate-y-0"
								></div>
							</a>
							<a
								href="/support"
								class="rounded-xl border border-purple-700/50 bg-purple-900/10 px-8 py-4 text-center font-medium text-purple-300 backdrop-blur-sm transition-all hover:bg-purple-900/30 hover:text-purple-200 focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black focus:outline-none"
							>
								Get Support
							</a>
						</div>
					</div>
				</div>
			</section>
		</div>
	</div>
</div>
