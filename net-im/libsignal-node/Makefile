PORTNAME=	libsignal
DISTVERSIONPREFIX=	v
DISTVERSION=	0.31.0
CATEGORIES=	net-im
PKGNAMESUFFIX=	-node
DISTFILES=	libsignal-node-${DISTVERSION}-yarn-cache.tar.gz

MAINTAINER=	mikael@FreeBSD.org
COMMENT=	Platform-agnostic APIs used by the official Signal clients and servers
WWW=		https://github.com/signalapp/libsignal

LICENSE=	AGPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

FETCH_DEPENDS=	yarn-node18>0:www/yarn-node18
EXTRACT_DEPENDS=yarn-node18>0:www/yarn-node18
BUILD_DEPENDS=	llvm-config${LLVM_DEFAULT}:devel/llvm${LLVM_DEFAULT} \
		protoc:devel/protobuf \
		yarn:www/yarn-node18

USES=		cargo gmake python:build
USE_GITHUB=	yes
GH_ACCOUNT=	signalapp
GH_TUPLE=	google:boringssl:3b74ab506eff560da3d67bfac9f1caa68bf31fbd:boringssl \
		google:boringssl:ae223d6138807a13006342edfeef32e813246b39:boringssl_fips

CARGO_CRATES=	addr2line-0.20.0 \
		adler-1.0.2 \
		aead-0.4.3 \
		aes-0.7.5 \
		aes-gcm-0.9.2 \
		aes-gcm-siv-0.10.1 \
		aho-corasick-1.0.2 \
		android-tzdata-0.1.1 \
		android_system_properties-0.1.5 \
		anes-0.1.6 \
		anstyle-1.0.1 \
		anyhow-1.0.72 \
		argon2-0.5.1 \
		arrayref-0.3.7 \
		asn1-0.15.4 \
		asn1_derive-0.15.4 \
		async-trait-0.1.72 \
		autocfg-1.1.0 \
		backtrace-0.3.68 \
		base64-0.21.2 \
		base64ct-1.6.0 \
		bincode-1.3.3 \
		bindgen-0.62.0 \
		bit-set-0.5.3 \
		bit-vec-0.6.3 \
		bitflags-1.3.2 \
		bitflags-2.3.3 \
		blake2-0.10.6 \
		block-buffer-0.10.4 \
		block-modes-0.8.1 \
		block-padding-0.2.1 \
		bumpalo-3.13.0 \
		bytemuck-1.13.1 \
		byteorder-1.4.3 \
		bytes-1.4.0 \
		cast-0.3.0 \
		cc-1.0.81 \
		cesu8-1.1.0 \
		cexpr-0.6.0 \
		cfg-if-1.0.0 \
		chacha20-0.8.2 \
		chacha20poly1305-0.9.1 \
		chrono-0.4.26 \
		ciborium-0.2.1 \
		ciborium-io-0.2.1 \
		ciborium-ll-0.2.1 \
		cipher-0.3.0 \
		clang-sys-1.6.1 \
		clap-4.3.19 \
		clap_builder-4.3.19 \
		clap_lex-0.5.0 \
		cmake-0.1.48 \
		combine-4.6.6 \
		convert_case-0.4.0 \
		core-foundation-sys-0.8.4 \
		cpufeatures-0.2.9 \
		criterion-0.5.1 \
		criterion-plot-0.5.0 \
		crossbeam-channel-0.5.8 \
		crossbeam-deque-0.8.3 \
		crossbeam-epoch-0.9.15 \
		crossbeam-utils-0.8.16 \
		crypto-common-0.1.6 \
		ctr-0.7.0 \
		ctr-0.8.0 \
		darling-0.14.4 \
		darling_core-0.14.4 \
		darling_macro-0.14.4 \
		derive-where-1.2.1 \
		derive_builder-0.12.0 \
		derive_builder_core-0.12.0 \
		derive_builder_macro-0.12.0 \
		derive_more-0.99.17 \
		digest-0.10.7 \
		displaydoc-0.2.4 \
		downcast-rs-1.2.0 \
		dunce-1.0.4 \
		dyn-clonable-0.9.0 \
		dyn-clonable-impl-0.9.0 \
		dyn-clone-1.0.12 \
		either-1.9.0 \
		env_logger-0.10.0 \
		equivalent-1.0.1 \
		errno-0.3.2 \
		errno-dragonfly-0.1.2 \
		fastrand-2.0.0 \
		fiat-crypto-0.1.20 \
		fixedbitset-0.4.2 \
		fnv-1.0.7 \
		foreign-types-0.5.0 \
		foreign-types-macros-0.2.3 \
		foreign-types-shared-0.3.1 \
		futures-core-0.3.28 \
		futures-io-0.3.28 \
		futures-macro-0.3.28 \
		futures-task-0.3.28 \
		futures-util-0.3.28 \
		generic-array-0.14.7 \
		getrandom-0.2.10 \
		ghash-0.4.4 \
		gimli-0.27.3 \
		glob-0.3.1 \
		half-1.8.2 \
		hashbrown-0.12.3 \
		hashbrown-0.14.0 \
		heck-0.3.3 \
		hermit-abi-0.3.2 \
		hex-0.4.3 \
		hex-literal-0.4.1 \
		hkdf-0.12.3 \
		hmac-0.12.1 \
		humantime-2.1.0 \
		iana-time-zone-0.1.57 \
		iana-time-zone-haiku-0.1.2 \
		ident_case-1.0.1 \
		indexmap-1.9.3 \
		indexmap-2.0.0 \
		is-terminal-0.4.9 \
		itertools-0.10.5 \
		itoa-1.0.9 \
		jni-0.19.0 \
		jni-sys-0.3.0 \
		jobserver-0.1.26 \
		js-sys-0.3.64 \
		lazy_static-1.4.0 \
		lazycell-1.3.0 \
		libc-0.2.147 \
		libloading-0.6.7 \
		libloading-0.7.4 \
		libm-0.2.7 \
		linkme-0.3.14 \
		linkme-impl-0.3.14 \
		linux-raw-sys-0.4.5 \
		log-0.4.19 \
		log-panics-2.1.0 \
		memchr-2.5.0 \
		memoffset-0.9.0 \
		minimal-lexical-0.2.1 \
		miniz_oxide-0.7.1 \
		mp4san-0.3.1 \
		multimap-0.8.3 \
		neon-0.10.1 \
		neon-build-0.10.1 \
		neon-macros-0.10.1 \
		neon-runtime-0.10.1 \
		nom-7.1.3 \
		num-traits-0.2.16 \
		num_cpus-1.16.0 \
		num_enum-0.6.1 \
		num_enum_derive-0.6.1 \
		object-0.31.1 \
		once_cell-1.18.0 \
		oorandom-11.1.3 \
		opaque-debug-0.3.0 \
		password-hash-0.5.0 \
		paste-1.0.14 \
		peeking_take_while-0.1.2 \
		petgraph-0.6.3 \
		pin-project-lite-0.2.10 \
		pin-utils-0.1.0 \
		platforms-3.0.2 \
		plotters-0.3.5 \
		plotters-backend-0.3.5 \
		plotters-svg-0.3.5 \
		poly1305-0.7.2 \
		polyval-0.5.3 \
		ppv-lite86-0.2.17 \
		pqcrypto-internals-0.2.4 \
		pqcrypto-kyber-0.7.6 \
		pqcrypto-traits-0.3.4 \
		proc-macro-crate-1.3.1 \
		proc-macro2-1.0.66 \
		proptest-1.2.0 \
		prost-0.9.0 \
		prost-build-0.9.0 \
		prost-derive-0.9.0 \
		prost-types-0.9.0 \
		quick-error-1.2.3 \
		quote-1.0.32 \
		rand-0.8.5 \
		rand_chacha-0.3.1 \
		rand_core-0.6.4 \
		rand_xorshift-0.3.0 \
		rayon-1.7.0 \
		rayon-core-1.11.0 \
		redox_syscall-0.3.5 \
		regex-1.9.1 \
		regex-automata-0.3.4 \
		regex-syntax-0.6.29 \
		regex-syntax-0.7.4 \
		rustc-demangle-0.1.23 \
		rustc-hash-1.1.0 \
		rustc_version-0.4.0 \
		rustix-0.38.6 \
		rusty-fork-0.3.0 \
		ryu-1.0.15 \
		same-file-1.0.6 \
		scopeguard-1.2.0 \
		semver-0.9.0 \
		semver-1.0.18 \
		semver-parser-0.7.0 \
		serde-1.0.180 \
		serde_derive-1.0.180 \
		serde_json-1.0.104 \
		sha-1-0.10.1 \
		sha2-0.10.7 \
		shlex-1.1.0 \
		slab-0.4.8 \
		smallvec-1.11.0 \
		static_assertions-1.1.0 \
		strsim-0.10.0 \
		subtle-2.5.0 \
		syn-1.0.109 \
		syn-2.0.28 \
		syn-mid-0.5.4 \
		tempfile-3.7.0 \
		termcolor-1.2.0 \
		thiserror-1.0.44 \
		thiserror-impl-1.0.44 \
		time-0.1.45 \
		tinytemplate-1.2.1 \
		toml_datetime-0.6.3 \
		toml_edit-0.19.14 \
		typenum-1.16.0 \
		unarray-0.1.4 \
		unicode-ident-1.0.11 \
		unicode-segmentation-1.10.1 \
		universal-hash-0.4.0 \
		unzip3-1.0.0 \
		uuid-1.4.1 \
		variant_count-1.1.0 \
		version_check-0.9.4 \
		wait-timeout-0.2.0 \
		walkdir-2.3.3 \
		wasi-0.10.0+wasi-snapshot-preview1 \
		wasi-0.11.0+wasi-snapshot-preview1 \
		wasm-bindgen-0.2.87 \
		wasm-bindgen-backend-0.2.87 \
		wasm-bindgen-macro-0.2.87 \
		wasm-bindgen-macro-support-0.2.87 \
		wasm-bindgen-shared-0.2.87 \
		web-sys-0.3.64 \
		which-4.4.0 \
		winapi-0.3.9 \
		winapi-i686-pc-windows-gnu-0.4.0 \
		winapi-util-0.1.5 \
		winapi-x86_64-pc-windows-gnu-0.4.0 \
		windows-0.48.0 \
		windows-sys-0.48.0 \
		windows-targets-0.48.1 \
		windows_aarch64_gnullvm-0.48.0 \
		windows_aarch64_msvc-0.48.0 \
		windows_i686_gnu-0.48.0 \
		windows_i686_msvc-0.48.0 \
		windows_x86_64_gnu-0.48.0 \
		windows_x86_64_gnullvm-0.48.0 \
		windows_x86_64_msvc-0.48.0 \
		winnow-0.5.3 \
		zeroize-1.6.0 \
		zeroize_derive-1.4.2 \
		curve25519-dalek,curve25519-dalek-derive,x25519-dalek@git+https://github.com/signalapp/curve25519-dalek?tag=signal-curve25519-4.0.0\#463e5c7cba32561ffee8a281c4455ff3c25660d4 \
		boring,boring-sys@git+https://github.com/signalapp/boring?branch=libsignal\#3809a7e1ca2f60a9495620da514f8432f148cde7 \
		snow@git+https://github.com/mcginty/snow.git?rev=586292364a30ecc74c785228b41e60b3ef03e773\#586292364a30ecc74c785228b41e60b3ef03e773

# RUSTFLAGS=-Clink-dead-code is required to have a functional libsignal-node binary:
# linkme is broken with https://github.com/dtolnay/linkme/commit/64e7c63c106848481bea8f66c4885b52c26ca9ec
# It's probably related to https://github.com/dtolnay/linkme/issues/49
MAKE_ENV=	HOME=${WRKDIR} \
		PYTHON=${PYTHON_CMD} \
		RUSTFLAGS=-Clink-dead-code \
		XDG_CACHE_HOME=${WRKDIR}/.cache

MAKE_ENV+=	RUSTC_BOOTSTRAP=aes,polyval

USE_LDCONFIG=	yes

PLIST_FILES=	lib/libsignal_node.so

NODE_ARCH=	${ARCH:S/aarch64/arm64/:S/amd64/x64/:S/i386/ia32/:C/powerpc64.*/ppc64/}
RUST_ARCH=	${ARCH:S/amd64/x86_64/:S/i386/i686/}

YARN_TIMESTAMP=	1661146515

.include <bsd.port.options.mk>

.if ${ARCH:Mpowerpc64*}
EXTRA_PATCHES=	${FILESDIR}/${ARCH}-patch-node_binding.gyp
.endif

pre-fetch:
	if [ ! -f ${DISTDIR}/libsignal-node-${DISTVERSION}-yarn-cache.tar.gz ]; \
		then ${MKDIR} ${WRKDIR}; \
		${ECHO_CMD} 'yarn-offline-mirror "./yarn-offline-cache"' >> \
			${WRKDIR}/.yarnrc; \
		${CP} ${FILESDIR}/node/package.json ${FILESDIR}/node/yarn.lock ${WRKDIR}; \
		cd ${WRKDIR} && ${SETENV} HOME=${WRKDIR} XDG_CACHE_HOME=${WRKDIR}/.cache \
			yarn --frozen-lockfile --ignore-scripts; \
		${MTREE_CMD} -cbnSp yarn-offline-cache | ${MTREE_CMD} -C | ${SED} \
			-e 's:time=[0-9.]*:time=${YARN_TIMESTAMP}.000000000:' \
			-e 's:\([gu]id\)=[0-9]*:\1=0:g' \
			-e 's:flags=.*:flags=none:' \
			-e 's:^\.:./yarn-offline-cache:' > yarn-offline-cache.mtree; \
		${TAR} cJf ${DISTDIR}/libsignal-node-${DISTVERSION}-yarn-cache.tar.gz  \
			@yarn-offline-cache.mtree; \
		${RM} -r ${WRKDIR}; \
	fi

post-patch:
	${REINPLACE_CMD} "s#python3#${PYTHON_CMD}#" \
		${WRKSRC}/node/binding.gyp

# Check hash here: https://github.com/signalapp/boring/tree/libsignal/boring-sys/deps
post-extract:
	${MV} ${WRKDIR}/boringssl-3b74ab506eff560da3d67bfac9f1caa68bf31fbd/* ${WRKDIR}/boring-3809a7e1ca2f60a9495620da514f8432f148cde7/boring-sys/deps/boringssl
	${MV} ${WRKDIR}/boringssl-ae223d6138807a13006342edfeef32e813246b39/* ${WRKDIR}/boring-3809a7e1ca2f60a9495620da514f8432f148cde7/boring-sys/deps/boringssl-fips

	${CP} ${FILESDIR}/node/package.json ${WRKSRC}/node

do-build:
	${ECHO_CMD} 'yarn-offline-mirror "../yarn-offline-cache"' > ${WRKSRC}/.yarnrc
	${ECHO_CMD} 'nodedir "${LOCALBASE}"' >> ${WRKSRC}/.yarnrc
	cd ${WRKSRC}/node && \
		${SETENV} ${MAKE_ENV} yarn install --frozen-lockfile --ignore-optional --offline
	cd ${WRKSRC}/node && \
		${SETENV} ${MAKE_ENV} yarn tsc

do-install:
	${INSTALL_DATA} ${WRKSRC}/node/build/Release/obj.target/libsignal_client_freebsd_${NODE_ARCH}.node/geni/rust/${RUST_ARCH}-unknown-freebsd/release/libsignal_node.so \
		${STAGEDIR}${PREFIX}/lib/

.include <bsd.port.mk>
