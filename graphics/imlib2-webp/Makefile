PORTNAME=	imlib2-webp
PORTVERSION=	20160601
CATEGORIES=	graphics

MAINTAINER=	ports@FreeBSD.org
COMMENT=	WebP image loader plugin for Imlib 2
WWW=		https://www.hauweele.net/~gawen/imlib2-webp.html

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS=	libImlib2.so:graphics/imlib2 \
		libwebp.so:graphics/webp

CONFLICTS_INSTALL=	imlib2

USES=		gmake pkgconfig
USE_GITHUB=	yes
GH_ACCOUNT=	gawen947
GH_TAGNAME=	79b3da58f48

MAKEFILE=	makefile
PLIST_FILES=	lib/imlib2/loaders/webp.so

.include <bsd.port.mk>
