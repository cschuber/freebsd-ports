PORTNAME=	systemd
PORTVERSION=	219
DISTVERSIONSUFFIX=	-78.el7_9.7
PORTREVISION=	12
CATEGORIES=	devel linux
PKGNAMESUFFIX=	-libs

MAINTAINER=	emulation@FreeBSD.org
COMMENT=	Libraries for accessing systemd (Linux CentOS ${LINUX_DIST_VER})
WWW=		https://www.freedesktop.org/wiki/Software/systemd/

LICENSE=	LGPL21+

USES=		cpe linux:c7
CPE_VENDOR=	systemd_project
USE_LDCONFIG=	yes
USE_LINUX=	elfutils-libs libgcrypt libgpg-error lz4
USE_LINUX_RPM=	yes

LIB_DISTNAMES=	${PORTNAME}${PKGNAMESUFFIX}-${DISTVERSIONFULL}

.include <bsd.port.mk>
