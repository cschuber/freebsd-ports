PORTNAME=	Geo-GeoNames
PORTVERSION=	1.140
CATEGORIES=	misc perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-
DISTNAME=	Geo-GeoNames-${PORTVERSION:S|0$||}

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Perform geographical queries using GeoNames Web Services
WWW=		https://metacpan.org/release/Geo-GeoNames

LICENSE=	ART20
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-JSON>=1.14:converters/p5-JSON \
		p5-Mojolicious>=0:www/p5-Mojolicious \
		p5-XML-Simple>=2.13:textproc/p5-XML-Simple
TEST_DEPENDS=	p5-Test-Most>=0:devel/p5-Test-Most

USES=		perl5
USE_PERL5=	configure

NO_ARCH=	yes

.include <bsd.port.mk>
