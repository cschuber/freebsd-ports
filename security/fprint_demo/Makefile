PORTNAME=	fprint_demo
PORTVERSION=	20080303
PORTREVISION=	3
CATEGORIES=	security
MASTER_SITES=	DEBIAN/pool/main/f/${PORTNAME:C/_/-/}
DISTNAME=	${PORTNAME:C/_/-/}_${PORTVERSION}git.orig

MAINTAINER=	danfe@FreeBSD.org
COMMENT=	Demo and test application for libfprint
WWW=		http://www.reactivated.net/fprint/wiki/Fprint_demo

LIB_DEPENDS=	libfprint.so:security/libfprint

USES=		autoreconf desktop-file-utils gnome pkgconfig
USE_GNOME=	atk glib20 gtk20 pango

NO_WRKSUBDIR=	yes

GNU_CONFIGURE=	yes
CONFIGURE_ENV=	CRYPTO_CFLAGS=-I${OPENSSLINC} \
		CRYPTO_LIBS=-lcrypto

CFLAGS+=	-DHAVE_MEMMEM

.include <bsd.port.mk>
