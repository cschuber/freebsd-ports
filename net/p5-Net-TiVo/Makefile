PORTNAME=	Net-TiVo
PORTVERSION=	0.11
PORTREVISION=	1
CATEGORIES=	net perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	perl@FreeBSD.org
COMMENT=	Framework for accessing TiVo using XML/HTTP
WWW=		https://metacpan.org/release/Net-TiVo

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-libwww>=0:www/p5-libwww \
		p5-XML-Simple>=0:textproc/p5-XML-Simple \
		p5-Log-Log4perl>=0:devel/p5-Log-Log4perl \
		p5-Crypt-SSLeay>=0:security/p5-Crypt-SSLeay

USES=		perl5
USE_PERL5=	configure

.include <bsd.port.mk>
