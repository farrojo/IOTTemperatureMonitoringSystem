#ifndef CERTIFICATES_H
#define CERTIFICATES_H

const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"cert1\n" \
"-----END CERTIFICATE-----\n";

const char* client_cert = \
"-----BEGIN CERTIFICATE-----\n" \
"cert2\n" \
"-----END CERTIFICATE-----\n";

const char* client_key = \
"-----BEGIN PRIVATE KEY-----\n" \
"cert3\n" \
"-----END PRIVATE KEY-----\n";
// TODO: generating certicates
#endif
