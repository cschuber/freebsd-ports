PORTNAME=	mod_rpaf
PORTVERSION=	0.8.4
DISTVERSIONPREFIX=	v
PORTREVISION=	1
CATEGORIES=	www
PKGNAMESUFFIX=	2

MAINTAINER=	apache@FreeBSD.org
COMMENT=	Make proxied requests appear with client IP
WWW=		https://github.com/gnif/mod_rpaf/

LICENSE=	APACHE20

USES=		apache cpe

CPE_VENDOR=	thomas_eibner

USE_GITHUB=	yes
GH_ACCOUNT=	gnif

AP_FAST_BUILD=	yes
SHORTMODNAME=	rpaf

SRC_FILE=	mod_rpaf.c

APMOD_FILE=	200_mod_rpaf.conf.sample
PLIST_SUB+=	APMOD_FILE=${APMOD_FILE}
PLIST_FILES=	@sample\ ${APACHEETCDIR}/modules.d/200_${PORTNAME}.conf.sample \
		${APACHEMODDIR}/${PORTNAME}.so
SUB_FILES=	${APMOD_FILE}

PORTDOCS=	README.md

OPTIONS_DEFINE=	DOCS

post-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/${APACHEETCDIR}/modules.d ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKDIR}/${APMOD_FILE} ${STAGEDIR}${PREFIX}/${APACHEETCDIR}/modules.d
	${INSTALL_DATA} ${WRKSRC}/README.md ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
