PORTNAME=	Net_Geo
PORTVERSION=	1.0.5
CATEGORIES=	net pear

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Geographical locations based on Internet address
WWW=		https://pear.php.net/package/Net_Geo

BUILD_DEPENDS=	${PEARDIR}/Cache.php:sysutils/pear-Cache@${PHP_FLAVOR} \
		${PEARDIR}/XML/Serializer.php:devel/pear-XML_Serializer@${PHP_FLAVOR}
RUN_DEPENDS=	${PEARDIR}/Cache.php:sysutils/pear-Cache@${PHP_FLAVOR} \
		${PEARDIR}/XML/Serializer.php:devel/pear-XML_Serializer@${PHP_FLAVOR}

USES=		pear

.include <bsd.port.mk>
