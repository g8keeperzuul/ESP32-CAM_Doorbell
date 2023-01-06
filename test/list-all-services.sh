#!/bin/bash
# Usage: $0

source env.sh
  
curl -X GET -H "Authorization: Bearer ${HA_ACCESS_TOKEN}" \
     -H "Content-Type: application/json" \
     ${HA_BASE_URL}/services | python -m json.tool
