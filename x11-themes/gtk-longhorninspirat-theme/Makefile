PORTNAME=	longhorninspirat
PORTVERSION=	1.0
PORTREVISION=	10
CATEGORIES=	x11-themes gnome
MASTER_SITES=	http://freebsd.nsu.ru/distfiles/ LOCAL/danfe \
		https://bsdforge.com/projects/source/x11-themes/gtk-longhorninspirat-theme/
PKGNAMEPREFIX=	${TYPE}-
PKGNAMESUFFIX=	-theme
DISTNAME=	Longhorn_Inspirat

MAINTAINER=	danfe@FreeBSD.org
COMMENT=	Port of Windows XP theme Longhorn Inspirat

USES=		tar:bzip2
NO_BUILD=	yes

TYPE?=		gtk
THEME_NAME=	"${DISTNAME:S/_/ /}"
WRKSRC=		${WRKDIR}/${THEME_NAME}

.if ${TYPE} == gtk
THEME_DIR=	${PREFIX}/share/themes/${THEME_NAME}
PLIST_SUB+=	GTK20="" METACITY="@comment "
USES+=		gnome
USE_GNOME=	gtk20
.else	# metacity
THEME_DIR=	${PREFIX}/share/themes/${THEME_NAME}
PLIST_SUB+=	GTK20="@comment " METACITY=""
.endif

post-extract:
	@${RM} -r ${WRKSRC}/gtk-2.0/.Trash-roberto

do-install:
	@${MKDIR} ${STAGEDIR}${THEME_DIR}
	${INSTALL_DATA} ${WRKSRC}/index.theme ${STAGEDIR}${THEME_DIR}
.if ${TYPE} == gtk
	cd ${WRKSRC} && ${FIND} gtk-2.0 | \
		${CPIO} -pdu -R ${SHAREOWN}:${SHAREGRP} ${STAGEDIR}${THEME_DIR}
.else
	cd ${WRKSRC} && ${FIND} metacity-1 | \
		${CPIO} -pdu -R ${SHAREOWN}:${SHAREGRP} ${STAGEDIR}${THEME_DIR}
.endif

.include <bsd.port.mk>
