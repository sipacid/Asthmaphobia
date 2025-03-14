#!/bin/bash

# Configuration
SERVER="github@apollo"
REMOTE_DIR="/var/www/asthmaphobia.xyz/html/"
BUILD_DIR="./dist"
PUBLIC_KEY_FILE="/Users/eve/.ssh/apollo_github.pub"

# Build
echo "Building website..."
bun run build || {
	BUILD_ERROR=$(bun run build 2>&1 >/dev/null)
	echo "Build failed!"
	echo "Error: $BUILD_ERROR"
	exit 1
}

# Deploy
echo "Deploying website using rsync..."
rsync -avz --delete -e "ssh -i $PUBLIC_KEY_FILE" "$BUILD_DIR/" "$SERVER:$REMOTE_DIR" || {
	RSYNC_ERROR=$(rsync -avz --delete -e ssh "$BUILD_DIR/" "$SERVER:$REMOTE_DIR" 2>&1 >/dev/null)
	echo "Deployment failed!"
	echo "Error: $RSYNC_ERROR"
	exit 1
}

echo "Deployment complete!"
