PORTNAME=	p11-kit
PORTVERSION=	0.23.5
DISTVERSIONSUFFIX=	-3.el7
PORTREVISION=	1
CATEGORIES=	security linux

MAINTAINER=	emulation@FreeBSD.org
COMMENT=	Library for loading and enumerating of PKCS\#11 modules (Linux CentOS ${LINUX_DIST_VER})
WWW=		https://p11-glue.freedesktop.org/p11-kit.html

USES=		linux:c7
USE_LDCONFIG=	yes
USE_LINUX=	libtasn1
USE_LINUX_RPM=	yes

LIB_DISTNAMES=	${DISTNAME} \
		p11-kit-trust-${DISTVERSION}${DISTVERSIONSUFFIX}

DESCR=		${.CURDIR}/../${PORTNAME}/pkg-descr

OPTIONS_DEFINE=	DOCS

.include <bsd.port.mk>
