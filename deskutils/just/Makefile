PORTNAME=	just
DISTVERSION=	1.14.0
PORTREVISION=	4
CATEGORIES=	deskutils

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Just a command runner: handy way to save/run project-specific commands
WWW=		https://just.systems/

LICENSE=	CC0-1.0
LICENSE_FILE=	${WRKSRC}/LICENSE

BROKEN_armv7=	compilation fails: error[E0308]: mismatched types, see https://github.com/dotenv-rs/dotenv/issues/83

USES=		cargo
USE_GITHUB=	yes
GH_ACCOUNT=	casey

CARGO_CRATES=	aho-corasick-1.0.1 \
		ansi_term-0.12.1 \
		atty-0.2.14 \
		bitflags-1.3.2 \
		block-buffer-0.10.4 \
		bstr-0.2.17 \
		camino-1.1.4 \
		cc-1.0.79 \
		cfg-if-1.0.0 \
		clap-2.34.0 \
		cpufeatures-0.2.7 \
		cradle-0.2.2 \
		crypto-common-0.1.6 \
		ctor-0.1.26 \
		ctrlc-3.4.0 \
		derivative-2.2.0 \
		diff-0.1.13 \
		digest-0.10.7 \
		doc-comment-0.3.3 \
		dotenvy-0.15.7 \
		edit-distance-2.1.0 \
		either-1.8.1 \
		env_logger-0.10.0 \
		errno-0.3.1 \
		errno-dragonfly-0.1.2 \
		executable-path-1.0.0 \
		fastrand-1.9.0 \
		generic-array-0.14.7 \
		getopts-0.2.21 \
		getrandom-0.2.9 \
		heck-0.3.3 \
		heck-0.4.1 \
		hermit-abi-0.1.19 \
		hermit-abi-0.3.1 \
		humantime-2.1.0 \
		instant-0.1.12 \
		io-lifetimes-1.0.11 \
		is-terminal-0.4.7 \
		itoa-1.0.6 \
		lazy_static-1.4.0 \
		lexiclean-0.0.1 \
		libc-0.2.144 \
		linked-hash-map-0.5.6 \
		linux-raw-sys-0.3.8 \
		log-0.4.18 \
		memchr-2.5.0 \
		nix-0.26.2 \
		once_cell-1.17.2 \
		output_vt100-0.1.3 \
		pretty_assertions-1.3.0 \
		proc-macro-error-1.0.4 \
		proc-macro-error-attr-1.0.4 \
		proc-macro2-1.0.59 \
		pulldown-cmark-0.9.3 \
		pulldown-cmark-to-cmark-10.0.4 \
		quote-1.0.28 \
		redox_syscall-0.3.5 \
		regex-1.8.3 \
		regex-automata-0.1.10 \
		regex-syntax-0.7.2 \
		rustix-0.37.19 \
		rustversion-1.0.12 \
		ryu-1.0.13 \
		serde-1.0.163 \
		serde_derive-1.0.163 \
		serde_json-1.0.96 \
		sha2-0.10.6 \
		similar-2.2.1 \
		snafu-0.7.4 \
		snafu-derive-0.7.4 \
		static_assertions-1.1.0 \
		strsim-0.8.0 \
		structopt-0.3.26 \
		structopt-derive-0.4.18 \
		strum-0.24.1 \
		strum_macros-0.24.3 \
		syn-1.0.109 \
		syn-2.0.18 \
		target-2.0.0 \
		tempfile-3.5.0 \
		temptree-0.2.0 \
		term_size-0.3.2 \
		termcolor-1.2.0 \
		textwrap-0.11.0 \
		typed-arena-2.0.2 \
		typenum-1.16.0 \
		unicase-2.6.0 \
		unicode-ident-1.0.9 \
		unicode-segmentation-1.10.1 \
		unicode-width-0.1.10 \
		uuid-1.3.3 \
		vec_map-0.8.2 \
		version_check-0.9.4 \
		wasi-0.11.0+wasi-snapshot-preview1 \
		which-4.4.0 \
		winapi-0.3.9 \
		winapi-i686-pc-windows-gnu-0.4.0 \
		winapi-util-0.1.5 \
		winapi-x86_64-pc-windows-gnu-0.4.0 \
		windows-sys-0.45.0 \
		windows-sys-0.48.0 \
		windows-targets-0.42.2 \
		windows-targets-0.48.0 \
		windows_aarch64_gnullvm-0.42.2 \
		windows_aarch64_gnullvm-0.48.0 \
		windows_aarch64_msvc-0.42.2 \
		windows_aarch64_msvc-0.48.0 \
		windows_i686_gnu-0.42.2 \
		windows_i686_gnu-0.48.0 \
		windows_i686_msvc-0.42.2 \
		windows_i686_msvc-0.48.0 \
		windows_x86_64_gnu-0.42.2 \
		windows_x86_64_gnu-0.48.0 \
		windows_x86_64_gnullvm-0.42.2 \
		windows_x86_64_gnullvm-0.48.0 \
		windows_x86_64_msvc-0.42.2 \
		windows_x86_64_msvc-0.48.0 \
		yaml-rust-0.4.5 \
		yansi-0.5.1
PLIST_FILES=	bin/${PORTNAME}

OPTIONS_DEFINE=		COMPLETIONS
OPTIONS_DEFAULT=	COMPLETIONS

COMPLETIONS_DESC=		Build and install bash, fish and zsh shell completions
COMPLETIONS_PLIST_FILES=	share/bash-completion/completions/${PORTNAME} \
				share/fish/vendor_completions.d/${PORTNAME}.fish \
				share/zsh/site-functions/_${PORTNAME}

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/${PORTNAME}

post-install-COMPLETIONS-on:
.for _shell in bash fish zsh
	${STAGEDIR}${PREFIX}/bin/${PORTNAME} --completions ${_shell} \
		>${STAGEDIR}${PREFIX}/${COMPLETIONS_PLIST_FILES:M*${_shell}*}
.endfor

.include <bsd.port.mk>
