PORTNAME=	rtiff
PORTVERSION=	1.4.8
PORTREVISION=	1
CATEGORIES=	graphics
DISTNAME=	${PORTNAME}_${PORTVERSION}

MAINTAINER=	tota@FreeBSD.org
COMMENT=	TIFF reader for R
WWW=		https://cran.r-project.org/web/packages/rtiff/

LICENSE=	GPLv3

LIB_DEPENDS=	libtiff.so:graphics/tiff
CRAN_DEPENDS=	R-cran-pixmap>0:graphics/R-cran-pixmap
BUILD_DEPENDS=	${CRAN_DEPENDS}
RUN_DEPENDS=	${CRAN_DEPENDS}

USES=		cran:auto-plist,compiles

.include <bsd.port.mk>
