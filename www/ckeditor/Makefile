PORTNAME=	ckeditor
PORTVERSION=	4.21.0
CATEGORIES=	www
MASTER_SITES=	https://download.cksource.com/CKEditor/CKEditor/CKEditor%20${PORTVERSION}/
DISTNAME=	ckeditor_${PORTVERSION}_full

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	WYSIWYG editor to be used inside web page
WWW=		https://ckeditor.com/ \
		https://github.com/ckeditor/ckeditor4

LICENSE=	GPLv2+ LGPL21+ MPL11 MPL20
LICENSE_COMB=	dual
LICENSE_FILE=	${WRKSRC}/LICENSE.md

USES=		cpe zip

NO_ARCH=	yes
NO_BUILD=	yes
WRKSRC=		${WRKDIR}/ckeditor

do-install:
	cd ${WRKSRC}/ && ${COPYTREE_SHARE} . ${STAGEDIR}${WWWDIR}

.include <bsd.port.mk>
