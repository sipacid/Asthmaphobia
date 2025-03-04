FROM oven/bun:1 AS base
WORKDIR /usr/src/app

# install dependencies into temp directory
# this will cache them and speed up future builds
FROM base AS install
RUN bun install -g @sveltejs/kit
RUN mkdir -p /temp/dev
COPY package.json bun.lock svelte.config.js /temp/dev/
RUN cd /temp/dev && bun install --frozen-lockfile

RUN mkdir -p /temp/prod
COPY package.json bun.lock svelte.config.js /temp/prod/
RUN cd /temp/prod && bun add -d svelte-adapter-bun && bun install --frozen-lockfile --production

# copy node_modules from temp directory
# then copy all (non-ignored) project files into the image
FROM base AS prerelease
RUN bun install -g @sveltejs/kit
COPY --from=install /temp/dev/node_modules node_modules
COPY . .

RUN bun svelte-kit sync

# test & build
ENV NODE_ENV=production
RUN bun test
RUN bun run build

# copy production dependencies and source code into final image
FROM base AS release
COPY --from=install /temp/prod/node_modules node_modules
COPY --from=prerelease /usr/src/app/build ./build
COPY --from=prerelease /usr/src/app/package.json .

# run the app
USER bun
EXPOSE 3000/tcp
ENTRYPOINT [ "bun", "./build/index.js" ]

