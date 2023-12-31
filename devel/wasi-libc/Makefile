PORTNAME=	wasi-libc
DISTVERSION=	g20210923
CATEGORIES=	devel

MAINTAINER=	vishwin@FreeBSD.org
COMMENT=	C standard library for WebAssembly System Interface
WWW=		https://github.com/CraneStation/wasi-libc

LICENSE=	APACHE20 MIT LLVM2
LICENSE_COMB=	multi
LICENSE_FILE_APACHE20=	${WRKSRC}/LICENSE-APACHE
LICENSE_FILE_MIT=	${WRKSRC}/LICENSE-MIT
LICENSE_FILE_LLVM2=	${WRKSRC}/LICENSE-APACHE-LLVM
LICENSE_NAME_LLVM2=	Apache License 2.0 with LLVM Exceptions
LICENSE_PERMS_LLVM2=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

BUILD_DEPENDS=	clang${LLVM_VERSION}:devel/llvm${LLVM_VERSION}

USES=		gmake
USE_GITHUB=	yes
GH_ACCOUNT=	WebAssembly
GH_TAGNAME=	ad5133410f66b93a2381db5b542aad5e0964db96
GH_TUPLE=	WebAssembly:WASI:ef8c1a53fe:wasi/tools/wasi-headers/WASI
NO_ARCH=	yes
LLVM_VERSION?=	13

ALL_TARGET=	finish

# NOTE: matches the https://github.com/CraneStation/wasi-sdk
WASI_SYSROOT=	${PREFIX}/share/wasi-sysroot

# NOTE: our llvm ports don't ship stdarg/stddef clang headers, so they're in FILESDIR
#       and we install them to the sysroot

MAKE_ENV=	INSTALL_DIR=${STAGEDIR}${WASI_SYSROOT} \
		WASM_AR=${LOCALBASE}/bin/llvm-ar${LLVM_VERSION} \
		WASM_CC=${LOCALBASE}/bin/clang${LLVM_VERSION} \
		WASM_CFLAGS="-O2 -DNDEBUG -isystem ${FILESDIR}" \
		WASM_NM=${LOCALBASE}/bin/llvm-nm${LLVM_VERSION}

# NOTE: phony targets cause make install to rebuild everything
#       https://github.com/CraneStation/wasi-libc/issues/156
post-patch:
	${REINPLACE_CMD} -e 's|install: finish|install:|' ${WRKSRC}/Makefile

post-install:
	${INSTALL_DATA} ${FILESDIR}/stdarg.h ${STAGEDIR}${WASI_SYSROOT}/include/
	${INSTALL_DATA} ${FILESDIR}/stddef.h ${STAGEDIR}${WASI_SYSROOT}/include/

.include <bsd.port.mk>
